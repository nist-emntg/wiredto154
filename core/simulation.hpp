#ifndef WIREDTO154_MODELS_SIMULATION_H
#define WIREDTO154_MODELS_SIMULATION_H

#include "types.hpp"
#include "models/coordinate.hpp"
#include "models/IEEE802154.hpp"
#include "models/modulation.hpp"
#include "models/node.hpp"
#include "models/pathlossmodel.hpp"
#include "network/frame.hpp"
#include "network/server.hpp"

#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/shared_ptr.hpp>
#include <exception>
#include <string>
#include <utility>
#include <vector>

class Simulation {
	public:
		typedef boost::mt19937 rng;
		typedef boost::uniform_real<double> uniform_dist;
		typedef boost::variate_generator<rng &, uniform_dist> vargen;

		/* first node list is the list of nodes that will receive the packet
		 * second node list is the list of nodes that will receive a damaged packet */
		typedef std::pair<Node<>::node_list, Node<>::node_list> reception_status;
		static rng randomness;
		void load(const std::string & filename);
		static Simulation & get(void);
		void set_seed(int seed) { randomness.seed(seed); }
		void set_modulation(std::string & modname);
		void set_pathloss_model(std::string & model, std::vector<std::string> options);
		void set_multicast_parameter(std::string & mcast_addr, int mcast_port);
		Node<>::node_map nodes;
		std::string list_nodes(void);
		bool is_properly_configured(std::string & error_msg);
		reception_type receivePacket(Node<>::node_ptr sender,
                           Node<>::node_ptr receiver,
						   const Frame::frame & msg);
		reception_status whoReceivedPacket(Node<>::node_ptr sender,
										const Frame::frame & msg);
		void start(void) { io_service.run(); }
		void stop(int node);

		struct exception_on_simulation_loading: std::exception {
            char const * what() const throw() { return ""; }
		};
		friend void sim_end_handler(int);
	private:
		bool initialized;
		void init(void);
		uniform_dist randvar;
		boost::shared_ptr<vargen> randgen;
		boost::asio::io_service io_service;
		boost::shared_ptr<PathLossModel> pathloss;
		Modulation::modulation_ptr modulation;
		Server::server_list servers;
		Simulation (): randvar(0.0, 1.0) {
			randgen = boost::shared_ptr<vargen>(new vargen(randomness, randvar));
			initialized = false; }
};


#endif /* WIREDTO154_MODELS_SIMULATION_H */
