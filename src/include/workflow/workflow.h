/* @file workflow.h
 *
 * declares classes for a single worflow which is a directed graph of
 * WorkNodes
 */
#ifndef MV_WORKFLOW_H
#define MV_WORKFLOW_H

namespace mv {

  class WorkNode;

  class Process {
  public:
    /* returns the single starting worknode */
    Node *getSource();
    Node *getSink();
    unsigned long getFlowId();

  private:
    WorkNode *_source_node;
    unsigned long _flow_id;
    
    
  };

} /* mv */

#endif /* MV_WORKFLOW_H */
