#ifndef CQL_ROUND_ROBIN_POLICY_HPP_
#define CQL_ROUND_ROBIN_POLICY_HPP_

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/atomic.hpp>

#include "cql/internal/cql_rand.hpp"
#include "cql/policies/cql_load_balancing_policy.hpp"

namespace cql {
	class cql_host_t;

	class cql_round_robin_query_plan_t: public cql_query_plan_t {
	public:
		cql_round_robin_query_plan_t(
			const boost::shared_ptr<cql_cluster_t>& cluster, 
			unsigned index);

		// Returns next host to query.
		virtual boost::shared_ptr<cql_host_t>
		next_host_to_query();

	private:
		unsigned										_index;
		unsigned										_current;
		std::vector<boost::shared_ptr<cql_host_t>>		_hosts;
	};

	class cql_round_robin_policy_t: 
		public cql_load_balancing_policy_t,
		boost::noncopyable
	{
	public:
		cql_round_robin_policy_t()
			: _cluster(),
			  _index(0) { }

		virtual void 
		init(const boost::shared_ptr<cql_cluster_t>& cluster);

		virtual cql_host_distance_enum 
		distance(const cql_host_t* host);

		virtual boost::shared_ptr<cql_query_plan_t> 
		new_query_plan(const boost::shared_ptr<cql_query_t>& query);

	private:
		boost::shared_ptr<cql_cluster_t> _cluster;
		boost::atomic<unsigned> _index;
	};
}

#endif