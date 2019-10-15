#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

//  change less to less_equal for multiset
template<typename T, typename cmp = less<T>>
using OrderedSet = tree<T, null_type, cmp, rb_tree_tag,
tree_order_statistics_node_update>;

OrderedSet<ll> oset;