#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C" {
#endif


void InitApp(void);
void HandleEventsApp(struct gecko_cmd_packet *evt);


#ifdef __cplusplus
};
#endif

#endif // APP_H
