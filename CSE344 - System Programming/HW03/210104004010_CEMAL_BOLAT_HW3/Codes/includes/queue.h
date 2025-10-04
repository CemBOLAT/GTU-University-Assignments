// queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include "types.h"

void insertRequest(t_data* data, SatelliteRequest* request);
SatelliteRequest* popHighestPriorityRequest(t_data* data);
void removeRequestFromQueue(t_data* data, int request_id);


#endif // QUEUE_H
