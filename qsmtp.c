#include <stdio.h>
#include <string.h>
#define KXVER 3

#include "k.h"
#include "smtp.h"

#define setVar(f) if(strcmp(key, "f")==0) {fields--;f = value;}

K add(K x) {
  if (x->t != -KJ) krr("type");
  return kj((x -> j)+2);
}

K send_mail(K x);

K send_mail(K x) {
  if(xt != XD) krr("type");
  char *server, *port, *user, *pass, *from, *from_name, *subject, *body, *to, *to_name, *auth;

  char *key;
  char* value;
  int fields = 8;
  int dict_size = kK(x)[0] -> n;
  for(int i = 0; i<dict_size; i++){
    key = kS(kK(x)[0])[i];
    value = (char*) kC(kK(kK(x)[1])[i]);
    setVar(server);
    setVar(port);
    setVar(user);
    setVar(pass);
    setVar(from);
    setVar(from_name);
    setVar(subject);
    setVar(body);
    setVar(to);
    setVar(to_name);
    setVar(auth);
  }

  struct smtp *smtp;
  int rc;
  rc = smtp_open(server, port, SMTP_SECURITY_NONE, SMTP_NO_CERT_VERIFY, NULL, &smtp);
  rc = smtp_auth(smtp,
                 SMTP_AUTH_PLAIN,
                 user,
                 pass);
  rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_FROM,
                        from,
                        from_name);
  rc = smtp_address_add(smtp,
                        SMTP_ADDRESS_TO,
                        to,
                        to_name);
  rc = smtp_header_add(smtp,
                       "Subject",
                       subject);
  rc = smtp_mail(smtp,
                 body);
  rc = smtp_close(smtp);
  if(rc != SMTP_STATUS_OK){
    fprintf(stderr, "smtp failed: %s\n", smtp_status_code_errstr(rc));
    return ki(1);
  }
  return ki(0);
  // K keys[sizeof(kK(x)[0])/sizeof(kK(x)[0][0])];
  // memcpy(keys, kK(x)[0], sizeof(kK(x)[0])/sizeof(kK(x)[0][0]));


}

// K send_mail(K server, K port, K user, K pass, K from, K from_name, K subject, K body, K to, K to_name) {
//   if (server->t != KC ||port -> t != KC || user -> t != KC || pass -> t != KC || from -> t != KC || from_name -> t != KC || subject -> t != KC || body -> t != KC || to -> t != KC || to_name -> t != KC ) krr("type");
//   int rc;
//   struct smtp *smtp;
//   rc = smtp_open(kC(server),kC(port), SMTP_SECURITY_NONE, SMTP_NO_CERT_VERIFY, NULL, &smtp);
//   return ki(rc)
//   memcpy(sv, kS(server), server->n);
// }
