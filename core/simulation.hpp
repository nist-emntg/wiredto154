#ifndef WIREDTO154_MODELS_SIMULATION_H
#define WIREDTO154_MODELS_SIMULATION_H

#include "coordinate.hpp"
#include "modulation.hpp"
#include "node.hpp"
#include "pathlossmodel.hpp"
#include "server.hpp"

#include <boost/asio.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <map>

class Simulation {
	public:
		typedef boost::mt19937 rng;
		static rng randomness;
		void load(const char * filename);
		static Simulation & get(void);
		void set_seed(int seed) { randomness.seed(seed); }
		std::map<int, Node<>::node_ptr> nodes;
	private:
		bool initialized;
		void init(void);
		boost::asio::io_service io_service;
		boost::shared_ptr<PathLossModel> pathloss;
		boost::shared_ptr<Modulation> modulation;
		Server::server_list servers;
		Simulation () { randomness(); initialized = false; }
};

#endif /* WIREDTO154_MODELS_SIMULATION_H */