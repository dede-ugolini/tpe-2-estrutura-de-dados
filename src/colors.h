#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

#define WARNING(X) printf("%s%s %s\n", YELLOW, X, RESET)
#define ERROR(X) printf("%s%s %s\n", RED, X, RESET)
#define SUCESS(X) printf("%s%s %s\n", GREEN, X, RESET)
