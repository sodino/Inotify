#include <string.h>
#include <jni.h>

#include <sys/inotify.h>
#include <errno.h>
#include <unistd.h>

#include <android/log.h>
#define LOG_TAG "ANDROID_LAB"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_lab_sodino_inotify_MainActivity_hello(JNIEnv * env, jobject thiz) {
    return env->NewStringUTF("HelloWorld!A string from JNI.");
}

JNIEXPORT void JNICALL Java_lab_sodino_inotify_MainActivity_watchFile(JNIEnv * env) {
	LOGE("watchFile log...");
	int nfd;
	int res;
	char event_buf[512];

	int event_mask = IN_ALL_EVENTS;
	int event_count = 1;
	struct inotify_event *event;
	const char* file_name = "/sdcard";

	nfd = inotify_init();
	if(nfd < 0) {
		LOGE("inotify_init failed, %s\n", strerror(errno));
		return;
	}

	res = inotify_add_watch(nfd, file_name, event_mask);
	if(res < 0) {
		LOGE("inotify_add_watch failed for %s, %s\n", file_name, strerror(errno));
		return;
	}

	while(1) {
		int event_pos = 0;
		LOGE("CALL read()");
		res = read(nfd, event_buf, sizeof(event_buf));
		LOGE("RETURN read()");
		if(res < (int)sizeof(*event)) {
			if(errno == EINTR) {
				continue;
			}
			LOGE("could not get event, %s\n", strerror(errno));
			break;
		}

		while(res >= (int)sizeof(*event)) {
			int event_size;
			event = (struct inotify_event *)(event_buf + event_pos);
			LOGE("%s: %08x %08x \"%s\"\n", file_name, event->mask, event->cookie, event->len ? event->name : "");

			if(event_count && --event_count == 0) {
				LOGE("return inner while.");
				break;
			}
			event_size = sizeof(*event) + event->len;
			res -= event_size;
			event_pos += event_size;
		}
	}
	LOGE("end watch code..");

}

#ifdef __cplusplus
}
#endif
