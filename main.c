/*
 * Copyright © 2012 Fabian Schuiki
 */

#include <stdio.h>
#include <cloud-service.h>

#include "service.h"


int main (int argc, char *argv[])
{
	struct twitter *twitter = twitter_create();
	if (twitter == NULL)
		return -1;
	
	/*struct cld_runloop *loop = cld_runloop_create();
	if (loop == NULL) {
		fprintf(stderr, "unable to create runloop\n");
		return 1;
	}
	
	cld_runloop_callback_fd(loop, runloop_fd, service);
	cld_runloop_callback_activity(loop, runloop_activity, service);
	
	int retval = cld_runloop_run(loop);*/
	int retval = twitter_run(twitter);
	
	twitter_destroy(twitter);
	return retval;
}
