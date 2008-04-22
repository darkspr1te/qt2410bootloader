#include "sys.h"
typedef char *va_list;
#define va_start(ap, p)		(ap = (char *) (&(p)+1))
#define va_arg(ap, type)	((type *) (ap += sizeof(type)))[-1]
#define va_end(ap)

#define KEY_BACKSPACE  0x08
#define KEY_ENTER      0x0d
#define KEY_ESC        0x1b

//taken from bios-lt

/*unsigned long strtoul(char *s, char **endptr, int radix)
{
	unsigned long ret;
	int i;

	ret = 0;

	while (*s != '\0') {
		if (*s >= '0' && *s <= '9')
			i = *s - '0';
		else if (*s >= 'a' && *s <= 'f')
			i = *s - 'a' + 0xa;
		else if (*s >= 'A' && *s <= 'F')
			i = *s - 'A' + 0xa;
		else
			break;

		if (i >= radix)
			break;

		ret = (ret * radix) + i;
		s++;
	}

	return ret;
}*/


char *gets(char *s, int n)
{
	char *p;
	int ch;

	p = s;
	while (1) {
		ch = getch();
		if (ch == KEY_ENTER)
			break;
		if (ch == KEY_BACKSPACE) {
			if (p > s) {
				p--;
				putch(ch);
				putch(' ');
				putch(ch);
			}
		} else if ((p - s) < (n - 1)) {
			/* visiable ascii chars */
			if (ch >= 32 && ch <= 126) {
				*p++ = (char)ch;
				putch(ch);
			}
		}
	}
	*p = '\0';

	return s;
}
unsigned long getul(unsigned long def, int radix)
{
	char buf[9];

	gets(buf, 9);
	if (buf[0] == '\0')
		return def;
	return strtoul(buf, NULL, radix);
}

unsigned char getuc(unsigned char def, int radix)
{
	char buf[4];
	unsigned long l;
	
	if (radix == 16)
		gets(buf, 3);
	else
		gets(buf, 4);

	if (buf[0] == '\0')
		return def;

	l = strtoul(buf, NULL, radix);
	if (l > 255)
		l = 255;

	return l;
}	



//taken from vivi
void putnstr(const char *str, int n)
{
	if (str == NULL)
		return;

	while (n && *str != '\0') {
		putch(*str);
		str++;
		n--;
	}
}

void putstr(const char *str)
{
	putnstr(str, strlen(str));
}

void print_0nd(char ch2, unsigned long l)
{
	unsigned long prod, t;
	int flag = 0;
	unsigned char ch;
	int i, j;

	ch2 = ch2 - '0';
	for (i = 15; i >= 0; i--) {
		prod = 1;
		t = l;
		for (j = 0; j < i; j++) {
			prod = prod * 10;
			t = t / 10;
		}
		ch = t;
		l -= prod * t;

		if (!flag && !ch && i >= ch2)
			continue;
		
		if (ch < 10)
			putch(ch + '0');
		else
			putch('?');

		flag = 1;
	}
}
void print_0nx(char ch2, unsigned long l)
{
	unsigned char ch;
	int i;

	ch2 = ch2 - '0';
	for (i = ch2 - 1; i >= 0; i--) {
		ch = (l >> (i * 4)) & 0x0f;
		if (ch < 10)
			putch(ch + '0');
		else
			putch(ch - 10 + 'a');
	}
}

int printf(const char *s, ...)
{
	va_list ap;
	unsigned long arg;
	const char *str;
	char ch1, ch2, ch3;

	va_start(ap, s);
	while (*s != 0) {
		if (*s == '%') {
			s++;
			ch1 = *s++;
			if (ch1 == 'l')
				ch1 = *s++;
			if (ch1 == 's') {
				str = va_arg(ap, unsigned char *);
				puts(str);
			} else if (ch1 == 'd') {
				arg = va_arg(ap, unsigned long);
				print_0nd('1', arg);
			} else {
				ch2 = *s++;
				ch3 = *s++;
				if (ch3 == 'l')
					ch3 = *s++;
				arg = va_arg(ap, unsigned long);
				if (ch3 == 'd')
					print_0nd(ch2, arg);
				else
					print_0nx(ch2, arg);
			}
		} else
			putch(*s++);
	}
	va_end(ap);
	return 0;
}