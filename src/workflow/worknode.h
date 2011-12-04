/* @file worknode.h
 * 
 * Declares classes for worknodes which contains an activity.
 */
#ifndef MDW_WORKFLOW_WORKNODE_H
#define MDW_WORKFLOW_WORKNODE_H


namespace mdw {
namespace workflow {

/* WorkNode represents a single node in a WorkFlow. It is the base class
   of all WorkNodes and will be accessed by both the runtime and any
   client programs */
class WorkNode {
public:
  enum WorkNodeTypeE {
    Source, /* no source, single destination */
    Sink,   /* single source, no destination */
    Seq,    /* single source, single destination */
    Join,   /* single source, multiple destination */
    Fork    /* single source, multiple destination */
  };

  void operator=(const WorkNode&); 
  WorkNode(const WorkNode&);
  virtual ~WorkNode();

protected:
  WorkNode(const unsigned nodetype);

  void print(ostream&) const;

  /* for debugging */
  void dump() const;

private:
  const unsigned int _workNodeType;  /* WorkNodeTypeE */
  
};
  
class WorkNodeSource : public WorkNode {
};


class WorkNodeFork : public WorkNode {
public:
  std::list<WorkNode *>& nextNodes();
};
  
class WorkNodeJoin : public WorkNode {
public:
  std::list<WorkNode *>& prevNodes();
};

} /* worknode */
} /* mdw */

#endif /* MDW_WORKFLOW_WORKNODE_H */
