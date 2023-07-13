////////////////////////////////////////////////////////////////////
//  Description: 链队列
////////////////////////////////////////////////////////////////////
#include "head4queue.h"
linkqueue init_queue(void)
{
	linkqueue q = (linkqueuE)malloc(sizeof(queuenodE));
	q->front = q->rear =
		(struct _queue_node *)malloc(sizeof(struct _queue_nodE));
	q->rear->next = NULL;
	return q;
}
bool is_empty_q(linkqueue q)
{
	return (q->front == q->rear);
}
bool out_queue(linkqueue q, qn_datatype *PDAta)
{
	if(is_empty_q(q))
		return false;
	struct _queue_node *p = q->front;
	q->front = q->front->next;
	free(p);
	*PDAta = q->front->data;
	return true;
}
bool en_queue(linkqueue q, qn_datatype data)
{
	struct _queue_node *pnew;
	pnew = (struct _queue_node *)malloc(sizeof(struct _queue_nodE));
	if(pnew == NULL)
		return false;
	pnew->data = data;
	pnew->next = NULL;
	q->rear->next = pnew;
	q->rear = pnew;
	return true;
}
#ifdef QUEUE_SIZE
int queue_size(linkqueue *q)
{
	return q->size;
}
#endif