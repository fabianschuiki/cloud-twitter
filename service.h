/*
 * Copyright © 2012 Fabian Schuiki
 */

#ifndef SERVICE_H
#define SERVICE_H


struct twitter {
	struct cld_service *service;
	struct cld_runloop *runloop;
};

struct twitter *twitter_create();
void twitter_destroy(struct twitter *twitter);

int twitter_run(struct twitter *twitter);


#endif