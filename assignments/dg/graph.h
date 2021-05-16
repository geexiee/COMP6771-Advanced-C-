#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <tuple>
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>

namespace gdwg {


template <typename N, typename E>
class Graph {
 public:
 typedef std::pair<std::shared_ptr<N>, std::shared_ptr<E>> Edge;

    // Custom Comparator used to sort the set of Edges 
    // based on Node then weight, in our Node class
    struct edge_set_comparator {
      bool operator() (const Edge& a, const Edge &b) const {
        if (*(a.first) == *(b.first)) {
          return *(a.second) < *(b.second);
        }

        return *(a.first) < *(b.first);
      }
    }; // new

    struct Node {
      Node(const N &val) : val(std::make_shared<N>(val)), edges_() {}
      std::shared_ptr<N> val;
      std::set<Edge, edge_set_comparator> edges_;


      friend bool operator==(const Node &a, const Node &b) {
          return *(a.val) ==  *(b.val);
      }

      friend bool operator<(const Node &a, const Node &b) {
          return *(a.val) < *(b.val);
      }

      bool InsertOutgoing(std::shared_ptr<N> dst, const E &weight) { // pass in shared ptr after finding node in set of nodes
          // std::cout << "InsertOutgoing(" << *dst << ", " << weight << ")" << std::endl;

          Edge e = std::make_pair(dst, std::make_shared<E>(weight));
          auto result = edges_.insert(std::move(e));
          // std::cout << *val << " has edges: " << edges_.size() << std::endl;
          return result.second;
      }

      bool EraseOutgoing(const N& dst, const E &weight) {
        for (auto it = edges_.cbegin(); it != edges_.cend(); ++it) {
          if (*(it->first) == dst && *(it->second) == weight) { // found
            edges_.erase(it);
            return true;
          }
        }
        // not found
        return false;
      }

      /*void ReplaceOutgoing(const Node &new_dst, const Node &old_dst) {
        for (Edge e : edges_) {
          if (*(e.first) == old_dst) {
            InsertOutgoing(new_dst.val, *(e.second));   // insert the new edge
            edges_.erase(e);                      // delete the old edge
          }
        }
      }*/

      void CleanOutgoing(const N &src) {
        // std::cout << "CleanOutgoing(" << src << ")" << std::endl;
        auto it = edges_.cbegin();
        while (it != edges_.cend()) {
          // std::cout << " *(it->first): " << *(it->first) << std::endl;
          
          if (*(it->first) == src) { // found a dst which is an src
              edges_.erase(it++);
          } else {
              ++it;
          }
        }
      }

      bool HasOutgoing(const N &dst) const {
        for (auto it = edges_.cbegin(); it != edges_.cend(); ++it) {
          if (*(it->first) == dst) {
              return true;
          }
        }
        return false;
      }

      typename std::set<Edge>::const_iterator FindEdge(const N &dst, const E& weight) const {
        for (auto it = edges_.cbegin(); it != edges_.cend(); ++it) {
          if (*(it->first) == dst && *(it->second) == weight) {
            return it;
          }
        }
        return edges_.cend();
      }

      std::set<N> GetOutgoing() const {
        std::set<N> outgoing;
        for (auto it = edges_.cbegin(); it != edges_.cend(); ++it) {
          outgoing.emplace(*(it->first));
        }

        return outgoing;
      }

      std::vector<E> GetDestWeights(const N &dst) const {
        std::cout << *this;
        std::vector<E> weights;
        for (auto it = edges_.cbegin(); it != edges_.cend(); ++it) {
          if (*(it->first) == dst){
            weights.emplace_back(*(it->second));
          }
        }
        // std::sort(weights.begin(), weights.end());
        return weights;
      }

      friend std::ostream& operator<<(std::ostream &os, const Node &node) {
          // std::cout << "number of edges for node " << *(node.val) << " is " << node.edges_.size() << std::endl;
          os << *(node.val) << " (" << std::endl;
          for (auto it = node.edges_.cbegin(); it != node.edges_.cend(); ++it) {
              os << "  " << *(it->first) << " | " <<  *(it->second) << std::endl;
          }
          os << ")" << std::endl;

          return os;
      }
    };


  
  class const_iterator {
    public:
    friend class Graph;
    using difference_type = std::ptrdiff_t;
    using value_type = std::tuple<const N, const N, const E>;
    using pointer = std::tuple<const N&, const N&, const E&>*;
    using reference = std::tuple<const N&, const N&, const E&>;
    using iterator_category = std::bidirectional_iterator_tag;

    explicit const_iterator(typename std::set<Node>::const_iterator nodes_pos, typename std::set<Edge>::const_iterator edges_pos) 
    : node_it_{ nodes_pos }, 
      edge_it_{ edges_pos } {};

    reference operator*() const { 
      return {*(node_it_->val), *(edge_it_->first), *(edge_it_->second)};
    };
    pointer operator->() const { return &(operator*()); };

    const_iterator& operator++() { 
      ++edge_it_;

      if (edge_it_ == node_it_->edges_.end()) {
        ++node_it_;
        // only iterating over edges, so if node has no edges, skip
        while(node_it_->edges_.size() == 0) { 
          ++node_it_;
        }
        edge_it_ = node_it_->edges_.begin();
      }

      return *this;
    }; // pre is the first one
      const_iterator operator++(int) { auto cpy {*this}; operator++(); return cpy; }; // post is the second

      const_iterator& operator--() {
          if (edge_it_ == node_it_->edges_.begin()) { // == begin
              --node_it_;

              while(node_it_->edges_.size() == 0) {
                  --node_it_;
              }

              edge_it_ = node_it_->edges_.end(); // == end
          }
          --edge_it_;
          return *this;
      };
    const_iterator operator--(int) { auto cpy {*this}; operator--(); return cpy; };
  
    friend bool operator==(const_iterator a, const_iterator b) {
      return a.node_it_ == b.node_it_ && a.edge_it_ == b.edge_it_;
    }

    friend bool operator!=(const_iterator a, const_iterator b){
      return !(a == b);
    }

    private:
      typename std::set<Node>::const_iterator node_it_;
      typename std::set<Edge>::const_iterator edge_it_;
  }; 

  // using const_iterator = const_iterator;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  
  const_iterator cbegin() const {
    // std::cout << nodes_.size() << std::endl;
    return const_iterator{nodes_.begin(), (nodes_.begin())->edges_.begin()};
  }
  const_iterator cend() const {
    // std::cout << (--(nodes_.end()))->edges_.size() << std::endl;
    return const_iterator{nodes_.end(), (nodes_.end())->edges_.begin()}; // you cant start at .end(), thats null
                                                                            // solution: have a prev pointer? like node* tail.
                                                                            // or set the end to be a dummy node
                                                                            // then have cend return the tail iterator of dummy
  }
  const_iterator begin() const { return cbegin(); }
  const_iterator end() const { return cend(); }
  const_reverse_iterator crbegin() const { return const_reverse_iterator{cend()}; }
  const_reverse_iterator crend() const { return const_reverse_iterator{cbegin()}; }
  const_reverse_iterator rbegin() const { return crbegin(); }
  const_reverse_iterator rend() const { return crend(); }

  const_iterator find(const N& a, const N& b, const E& weight) {
    const auto a_node = nodes_.find(Node{a});
    const auto b_node = a_node->FindEdge(b, weight);

    if (a_node == nodes_.end() || b_node == a_node->edges_.end()) {
      return cend();
    }

    return const_iterator(a_node, b_node);
  }

  bool erase(const N& src, const N& dst, const E& w);

  const_iterator erase(const_iterator it) {

    if (it == end()){
      return it;
    }

    auto src = std::get<0>(*it);
    auto dst = std::get<1>(*it);
    auto w = std::get<2>(*it);
    // increment the iterator to return the next element after deleted element
    ++it;
    auto result = erase(src, dst, w);

    if (!result) {
      return end();
    }

    
    return it;
  }
  

  // default constructor
  Graph() : nodes_() {}

  Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end) {
    for (auto it = start; it != end; ++it) {
      InsertNode(*it);
    }
  }

  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start, typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
    for (auto it = start; it != end; ++it) {
      InsertNode(std::get<0>(*it));
      InsertNode(std::get<1>(*it));
      InsertEdge(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it));
    }
  }

  Graph(std::initializer_list<N> init) {
    for (auto it = init.begin(); it != init.end(); ++it){
      InsertNode(*it);
    }
  }

  // COPY CONSTRUCTOR
  Graph(const Graph<N, E> &g) {
    // each node needs its own N on the heap now...
    // must do this first before you add the edges

    // implement graph iterator !! 

    for (auto it = g.begin(); it != g.end(); ++it) {
      InsertNode(std::get<0>(*it));
      InsertNode(std::get<1>(*it));
      InsertEdge(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it));
    } 
  }

  ~Graph() = default;
  //    METHODS

  // inserts node into a graph
  bool InsertNode(const N& val);
  // inserts edge into graph
  bool InsertEdge(const N& src, const N& dst, const E& w);
  // deletes node
  bool DeleteNode(const N&);
  bool Replace(const N& oldData, const N& newData);
  void MergeReplace(const N& oldData, const N& newData);
  void Clear();
  bool IsNode(const N& val);
  bool IsConnected(const N& src, const N& dst);
  std::vector<N> GetNodes();
  std::vector<N> GetConnected(const N& src);
  std::vector<E> GetWeights(const N& src, const N& dst);
  // FRIENDS

    friend bool operator==(const gdwg::Graph<N, E>& g1, const gdwg::Graph<N, E>& g2) {
        // check both graphs have same nodes and edges
        for (const auto n : g1.nodes_) {
            // checking nodes
            if (g2.nodes_.find(n) != g2.nodes_.end()) {
                auto n2_iterator = g2.nodes_.find(n);
                auto n2 = *n2_iterator;     // this is the corresponding node in g2
                // check edges
                for (auto e : n.edges_) {
                    // if the corresponding node in the second graph has the same edge, continue checking
                    // if it doesn't the graphs are not equal so return false
                    auto weight = *(e.second);
                    // iterate through the corresponding node in the second graph to find the same edge
                    unsigned long count = 0;
                    for (auto e2 : n2.edges_) {
                        if (*(e2.second) == weight) break;
                        count++;
                        if (count == n2.edges_.size()) {
                          return false; // if we reach the end of n2 then the edge doesnt exist
                        }
                    }
                }
            }
            // if the second graph doesn't contain the same node, return false
            else {
                return false;
            }
        }
        return true;
    }

    // using previously define == operator
    friend bool operator!=(const gdwg::Graph<N, E>& g1, const gdwg::Graph<N, E>& g2) {
        if (g1 == g2) return false;
        return true;
    }

    friend std::ostream& operator<<(std::ostream &os, const Graph<N, E> &graph) {
        //std::cout << "--- PRINTING OUT GRAPH --- " << std::endl;
        //std::cout << "nodes in graph: " << graph.nodes_.size() << std::endl;
        for (auto it = graph.nodes_.cbegin(); it != graph.nodes_.cend(); ++it) {
            os << *(it);
        }

      return os;
  }

private:
    std::set<Node> nodes_;
};



template <typename N, typename E>
bool Graph<N, E>::InsertNode(const N &val) {
    Node new_node{val};
    auto result = nodes_.insert(new_node);
    return result.second;
}

template <typename N, typename E>
bool Graph<N,E>::InsertEdge(const N& src, const N& dst, const E& w) {
    if (!IsNode(src) || !IsNode(dst)) {
      throw std::runtime_error("Cannot call Graph::InsertEdge when either src or dst node does not exist");
    }
    auto src_it = nodes_.find(Node{src});
    auto src_node = *(src_it); 
    auto dst_node = *(nodes_.find(Node{dst}));
    auto result = src_node.InsertOutgoing(dst_node.val, w);

    // since we can't modify set elements, we need to delete the previous elem
    // and then insert the new node with new edge connections
    nodes_.erase(src_it);
    nodes_.insert(src_node);
    return result;
}

template <typename N, typename E>
bool Graph<N,E>::DeleteNode(const N& val) {
    std::cout << "-- DeleteNode(" << val << ")" << std::endl;
    if (!IsNode(val)) return false; // if the node doesn't exist, there's nothing to delete

    auto val_it = nodes_.find(Node{val});
    nodes_.erase(val_it); 

     // then delete all the other shared_ptrs so ref_count == 0
     // and underlying object deleted ie no memory leak
    
    auto it = nodes_.begin();
    while (it != nodes_.end()) {

      auto clean_node = *it;
      clean_node.CleanOutgoing(val);
      nodes_.erase(it++);
      auto result = nodes_.insert(clean_node);
      if (result.second == false) return false;
    }

    return true;
}

template <typename N, typename E>
bool Graph<N,E>::Replace(const N& oldData, const N& newData) {
    if (!IsNode(oldData)) {
        throw std::runtime_error("Cannot call Graph::Replace on a node that doesn't exist");
    }

    if (IsNode(newData)) {
        return false;
    }

    auto replace_it = nodes_.find(Node{oldData});
    auto replace_node = *replace_it;
    nodes_.erase(replace_it);
    *(replace_node.val) = newData;
    auto result = nodes_.insert(replace_node);

    return result.second;
}

template <typename N, typename E>
void Graph<N,E>::MergeReplace(const N& oldData, const N& newData) {
    if (oldData == newData) return; // do nothing if old and new are the same

    if (!IsNode(oldData) || !IsNode(newData)) {
        throw std::runtime_error("Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph");
    }

    auto old_node_it = nodes_.find(Node{oldData});
    auto old_node = *old_node_it;       // this is the node being replaced

    auto new_node_it = nodes_.find(Node{newData});
    auto new_node = *new_node_it;   // this is the replacing node

    // iterate through each edge in the old node and replace with edge sourcing from the new node
    for (Edge e : old_node.edges_) {
        InsertEdge(*(new_node.val), *(e.first), *(e.second));        // insert a new edge from the replacing node to the previous dst
    }

    // now we need to connect all the incoming edges to the replacing node
    // iterate through each node in the graph and find ones that are outgoing to the old node
    for (auto n : nodes_) {
      //n.ReplaceOutgoing(new_node, old_node);
        for (auto e : n.edges_) {        // iterating through each edge in the node
            if (*(e.first) == oldData) {
                InsertEdge(*(n.val), *(new_node.val), *(e.second));   // insert the new edge
                n.edges_.erase(e);                      // delete the old edge
            }
        }
    }
  nodes_.erase(old_node_it); // delete the old node from the graph (along with it's outgoing edges, but incoming edges still exist)

  return;

    // need to completely remove the old node
        // if i delete the old node, how do i access it's existing edges that need to be redirected?
        // keep a copy of the old node (and hence a copy of all its edges)
        // iterate through every node and find outgoing edges to the old node. delete/replace those edges (using erase(iterator))
        // and replace with edges that now go to the new/replacing node
        // finally, go through the edges of the copied old node and recreate them with the replacing node

    // then connect the previous edges to the new node (create new edges)
    // then remove any duplicate edges

}

template <typename N, typename E>
bool Graph<N,E>::IsNode(const N &val) {
    return nodes_.find(Node{val}) != nodes_.end();
}

template <typename N, typename E>
void Graph<N,E>::Clear() {

    /* will call destructors on all fields and child classes (i believe)
    and since we are using smart pointers, underlying object will be
    clean up automatically*/
    nodes_.clear();
}

template <typename N, typename E>
bool Graph<N,E>::IsConnected(const N& src, const N& dst){

    if (!IsNode(src) || !IsNode(dst)) {
        throw std::runtime_error("Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
    }

    auto src_node = *(nodes_.find(Node{src}));

    return src_node.HasOutgoing(dst);

}

template <typename N, typename E>
std::vector<N> Graph<N,E>::GetNodes() {
  std::vector<N> vector_of_nodes;
  for (auto it = nodes_.cbegin(); it != nodes_.cend(); ++it) {
    vector_of_nodes.emplace_back((*(it->val)));
  }

  // std::sort(vector_of_nodes.begin(), vector_of_nodes.end());
  return vector_of_nodes;
}

template <typename N, typename E>
std::vector<N> Graph<N,E>::GetConnected(const N& src) {
  if (!IsNode(src)) {
    throw std::out_of_range("Cannot call Graph::GetConnected if src doesn't exist in the graph");
  }
  auto src_node = *(nodes_.find(Node{src}));
  auto connected_set = src_node.GetOutgoing();
  std::vector<N> connected_vector(connected_set.begin(), connected_set.end());
  return connected_vector;

}

template <typename N, typename E>
std::vector<E> Graph<N,E>::GetWeights(const N& src, const N& dst) {
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::out_of_range("Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
  }

  auto src_node = *(nodes_.find(Node{src}));
  return src_node.GetDestWeights(dst);

}

template <typename N, typename E>
bool Graph<N,E>::erase(const N& src, const N& dst, const E& w) {
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::runtime_error("Cannot call Graph::InsertEdge when either src or dst node does not exist");
  }

  auto src_it = nodes_.find(Node{src});
  auto src_node = *(src_it); 
  auto dst_node = *(nodes_.find(Node{dst}));

  auto result = src_node.EraseOutgoing(dst, w);

  // since we can't modify set elements, we need to delete the previous elem
  // and then insert the new node with new edge connections
  nodes_.erase(src_it);
  nodes_.insert(src_node);

  return result;
}


}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_