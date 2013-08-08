#include <unistd.h>
#include <linux/inotify.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WD_NUM 1
#define EVENT_NUM 16
#define MAX_BUF_SIZE 1024

/* the file being monitored */
char * monitored_files[] = {"."};

struct wd_name {
	int wd;
	char * name;
};

struct wd_name wd_array[WD_NUM];

char * event_array[] = {
	"File was accessed",
	"File was modified",
	"File attributes were changed",
	"writtable file closed",
	"Unwrittable file closed",
	"File was opened",
	"File was moved from X",
	"File was moved to Y",
	"Subfile was created",
	"Subfile was deleted",
	"Self was deleted",
	"Self was moved",
	"",
	"Backing fs was unmounted",
	"Event queued overflowed",
	"File was ignored"
};

int main(void)
{
	int fd, wd, len, tmp_len, i;
	char buffer[1024], strbuf[16], *offset;
	struct inotify_event * event;

	fd = inotify_init();
	if (fd < 0) {
		printf("Fail to initialize inotify.\n");
		exit(-1);
	}
	for (i=0; i<WD_NUM; i++) {
		wd_array[i].name = monitored_files[i];
		wd = inotify_add_watch(fd, wd_array[i].name, IN_ALL_EVENTS);
		if (wd < 0) {
			printf("Can't add watch for %s.\n", wd_array[i].name);
			exit(-1);
		}
		wd_array[i].wd = wd;
	while(len = read(fd, buffer, MAX_BUF_SIZE)) {
		offset = buffer;
		printf("Some events happened, len = %d.\n", len);
		event = (struct inotify_event *)buffer;
		while (((char *)event - buffer) < len) {
			if (event->mask & IN_ISDIR) {
				memcpy(strbuf, "Direcotory", 11);
			} else {
				memcpy(strbuf, "File", 5);
			}
			printf("Object type: %s\n", strbuf);
			for (i=0; i<WD_NUM; i++) {
				if (event->wd != wd_array[i].wd) {
					continue;
				} 
				printf("Object name: %s\n", wd_array[i].name);
				break;
			}
			printf("Event mask: %08X\n", event->mask);
			for (i=0; i<EVENT_NUM; i++) {
				if (event_array[i][0] == '\0') {
					continue;
				}
				if (event->mask & (1<<i)) {
					printf("Event: %s\n", event_array[i]);
				}
			}
			tmp_len = sizeof(struct inotify_event) + event->len;
			event = (struct inotify_event *)(offset + tmp_len); 
			offset += tmp_len;
		}
	}
}
