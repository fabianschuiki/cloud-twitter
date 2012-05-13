/*
 * Copyright © 2012 Fabian Schuiki
 */

#include <stdlib.h>
#include <string.h>
#include <cloud-service.h>

#include "service.h"


static struct cld_fd *
runloop_fd (int *count, void *data)
{
	struct twitter *twitter = data;
	return cld_service_get_fds(twitter->service, count);
}

static void
runloop_activity (struct cld_fd *fds, int count, void *data)
{
	struct twitter *twitter = data;
	cld_service_communicate(twitter->service, fds, count);
}


struct twitter *
twitter_create ()
{
	struct twitter *twitter;
	
	twitter = malloc(sizeof *twitter);
	if (twitter == NULL)
		return NULL;
	
	memset(twitter, 0, sizeof *twitter);
	
	twitter->service = cld_service_create();
	if (twitter->service == NULL) {
		free(twitter);
		return NULL;
	}
	
	twitter->runloop = cld_runloop_create();
	if (twitter->runloop == NULL) {
		cld_service_destroy(twitter->service);
		free(twitter);
		return NULL;
	}
	
	cld_runloop_callback_fd(twitter->runloop, runloop_fd, twitter);
	cld_runloop_callback_activity(twitter->runloop, runloop_activity, twitter);
	
	cld_service_set_name(twitter->service, "twitter");
	cld_service_send_descriptor(twitter->service);
	
	return twitter;
}

void
twitter_destroy (struct twitter *twitter)
{
	cld_service_destroy(twitter->service);
	free(twitter);
}


int
twitter_run (struct twitter *twitter)
{
	return cld_runloop_run(twitter->runloop);
}