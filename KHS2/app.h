#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C" {
#endif

#define APP_DEVNAME                  "BG%05u"
#define APP_DEVNAME_DEFAULT          "BG00000"
/* subtract 1 because of terminating NULL character */
#define APP_DEVNAME_LEN              (sizeof(APP_DEVNAME_DEFAULT) - 1)

#define APP_FIRM_VER_MAJOR                0
#define APP_FIRM_VER_MINOR                0
#define APP_FIRM_VER_BUILD                1

void InitApp(void);
void HandleEventsApp(struct gecko_cmd_packet *evt);

#ifdef __cplusplus
};
#endif

#endif // APP_H
