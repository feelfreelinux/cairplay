#include "BellLogger.h"
#include "PortAudioSink.h"
#include "dmap_parser.h"
#include <ifaddrs.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <raop.h>
#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace bell;
static void raop_sink_data_handler(const uint8_t *data, uint32_t len, u32_t playtime) {	
	// raop_sync.playtime = playtime;
	// raop_sync.len = len;

	// sink_data_handler(data, len);
}

static bool cmd_handler(raop_event_t event, ...) {
	// va_list args;	
	
	// va_start(args, event);
	
	// // handle audio event and stop if forbidden
	// if (!cmd_handler_chain(event, args)) {
	// 	va_end(args);
	// 	return false;
	// }

	// // now handle events for display
	// switch(event) {
	// case RAOP_SETUP:

	// 	break;
	// case RAOP_PLAY:
	// 	break;		
	// case RAOP_FLUSH:
	// 	break;		
	// case RAOP_STOP:
	// 	break;
	// case RAOP_METADATA: {
	// 	break;
	// }	
	// case RAOP_ARTWORK: {
	// 	break;
	// }
	// case RAOP_PROGRESS: {
	// 	break;
	// }	
	// default: 
	// 	break;
	// }
	
	// va_end(args);
	
	return true;
}

int main() {
	setDefaultLogger();
	auto sink = std::make_shared<PortAudioSink>();
	auto ver = dmap_version();
	// get own ip_addr

	// get the hostname of the server
	char hostname[128];
	if (gethostname(hostname, sizeof(hostname)) == -1) {
		std::cout << "Could not get the hostname of the server. Error: " << std::strerror(errno) << std::endl;
		return 1;
	}

	std::cout << "IP addresses for " << hostname << ":" << std::endl << std::endl;

	struct ifaddrs *networkInterfaceList, *p;

	getifaddrs(&networkInterfaceList); // get information about the network interfaces
	in_addr *addr;

	// iterate over all the network interfaces we got and try to extract their IP address
	for (p = networkInterfaceList; p != NULL; p = p->ifa_next) {
		char serverIPAddress[INET6_ADDRSTRLEN];
		std::string ipVersion;

		// get the pointer to the address itself,
		// different fields in IPv4 and IPv6:
		if (p->ifa_addr->sa_family == AF_INET) { // IPv4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ifa_addr;
			addr = &(ipv4->sin_addr);
			ipVersion = "IPv4";

			// if (p->ifa_data != 0) {
			// 	struct ifreq req;
			// 	strcpy(req.ifr_name, p->ifa_name);
			// 	if (ioctl(sd, SIOCGIFHWADDR, &req) != -1) {
			// 		uint8_t *mac = (uint8_t *)req.ifr_ifru.ifru_hwaddr.sa_data;
			// 		printf(
			// 			"%s:MAC[%02X:%02X:%02X:%02X:%02X:%02X]\n",
			// 			p->ifa_name,
			// 			mac[0],
			// 			mac[1],
			// 			mac[2],
			// 			mac[3],
			// 			mac[4],
			// 			mac[5]);
			// 	}
			// }
		} else {
			continue;
		}

		// take the IP address of our hostname and convert it into a readable format
		inet_ntop(p->ifa_addr->sa_family, addr, serverIPAddress, sizeof(serverIPAddress));

		// sometime the IP address is empty so only print if there is one
		if (std::strlen(serverIPAddress) > 0 && strcmp(p->ifa_name, "en0") == 0)
			std::cout << "Interface: " << std::setw(6) << std::left << p->ifa_name << " " << ipVersion << ": "
					  << serverIPAddress << std::endl;
	}

	freeifaddrs(networkInterfaceList); // free the linked list
    std::vector<uint8_t> mac = std::vector<uint8_t>({0, 1, 2, 3, 4, 5});
	raop_create((uint32_t) addr->s_addr, "Euphonium", mac.data(), 0, cmd_handler, (raop_data_cb_t) raop_sink_data_handler);
	return 0;
}
