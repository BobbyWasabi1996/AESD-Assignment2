#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
	openlog("writer", LOG_PID, LOG_USER);

	if (argc != 3) {
        	fprintf(stderr, "Error: Expected 2 arguments\n");
        	syslog(LOG_ERR, "Invalid number of arguments");
        	closelog();
        	return 1;
    	}

	const char *writefile = argv[1];
	const char *writestr = argv[2];

	if (writefile[0] == '\0') {
		fprintf(stderr, "Empty file path");
		syslog(LOG_ERR, "Empty file path");
		closelog();
		return 1;
	}

	FILE *file = fopen(writefile, "w");

	if (file == NULL) {
        	syslog(LOG_ERR, "Failed to open %s: %s", writefile, strerror(errno));
        	perror("fopen");
        	closelog();
        	return 1;
    	}

	syslog(LOG_DEBUG, "Writer %s to %s", writestr, writefile);

	if (fprintf(file, "%s\n", writestr) < 0) {
        	syslog(LOG_ERR, "Failed to write %s: %s", writefile, strerror(errno));
        	perror("fprintf");
        	fclose(file);
        	closelog();
        	return 1;
    	}

	closelog();
	return 0;
}
