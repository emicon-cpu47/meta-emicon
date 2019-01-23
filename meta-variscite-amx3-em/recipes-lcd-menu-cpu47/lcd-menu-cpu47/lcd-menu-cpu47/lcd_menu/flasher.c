/*
 * Система прошивки ЦПУ через Ethernet.
 * 
 * Задача клиента получить от сервера прошивку, установить ее, установить 
 * сетевые настроики полученные от сервера и перезапуститься.
 * Клиент не знает IP сервера, следовательно не знает совпадает ли его
 * собственный IP с сервером, что вероятно исходя из принципов работы ЦПУ в
 * паре. Соответвенно клиент меняет свои сетевые настройки на зарезервированные:
 * "192.168.254.254", "255.255.255.0", "192.168.254.1"
 * Затем клиент по UDP ищет сервер посылая широковещательные запросы.
 * Сервер принимая запрос на поиск сервера, отвечает передавая маску своей
 * сети. 
 * В ответе от сервера клиент получает маску, а также ip сервера и настраивает
 * свои сетевые параметры на сеть сервера. Далее клиент связывается с сервером
 * по TCP и получает прошивку.
 */

#include <errno.h>

#define PORT_UDP 7802
#define PORT_TCP 7803
#define REQUEST_FW_SERVER "WhoIsServer"
#define RESPOND_FW_SERVER "IAmServer"
#define REQUEST_FW "getfm"
#define STR_HOST_LEN 16
#define BUF_SIZE 8192
#define TIMEOUT_READING_UDP 5000 // 5 секунд
#define TIMEOUT_READING_TCP 5000
#define FW_FILE "/tmp/firmware.tar"
#define FW_FILE_RECEIVED "/usr/bin/codesys/update.tar"
#define FW_CREATE_SCRIPT "/etc/get_full_fmw.sh"
#define FW_UPDATE_SCRIPT "/etc/update_codesys_reboot.sh"
#define NETWORK_UPDATE_SCRIPT "/etc/net_file_create.sh"
#define EOF_STR "EOF"

void fw_manager(bool start);
int open_nonblock_udp_socket(void);
int open_nonblock_tcp_socket(void);

#include "server.c"
#include "client.c"

/*
 * Менеджер вызывается циклически с указанием режима работы.
 * При переходе в режим клиента больше не переключает режимы.
 * Клиент должен перегрузить ЦПУ по окончанию прошивки.
 */
void fw_manager(bool start_fw)
{
	static bool server_mode = true;

	/*
	 * После приема прошивки ПЛК перегрузится, поэтому тут самозамыкаемся
	 * в состоянии клиента без выхода из этого состояния.
	 */
	if (start_fw)
		server_mode = false;  

	server(server_mode);
	client(!server_mode);

	return;
}

/*
 * Открывает неблокирующий широковещательный UDP сокет.
 */
int open_nonblock_udp_socket(void)
{
	int bcast_sock;
	int broadcast_enable = 1;
	int non_blocking = 1;
	
	bcast_sock = socket(AF_INET, SOCK_DGRAM, 0);

	if(bcast_sock == -1) {
		fprintf(stderr, "UDP сокет НЕ создан!\n");
		return -1;
	}

	if (-1 == setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST,
		     &broadcast_enable, sizeof(broadcast_enable))) {
		fprintf(stderr, "UDP широковещательный режим НЕ установлен\n");
		return -1;
	}

	if (-1 == fcntl(bcast_sock, F_SETFL, O_NONBLOCK, non_blocking)) {
	    fprintf(stderr, "UDP failed to set non-blocking socket\n" );
	    return -1;
	}

	return bcast_sock;
}

/*
 * Открывает неблокирующий TCP сокет.
 */
int open_nonblock_tcp_socket(void)
{
	int sock;
	int non_blocking = 1;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock == -1) {
		fprintf(stderr, "open TCP socket failed!\n");
		return -1;
	}

	if (-1 == fcntl(sock, F_SETFL, O_NONBLOCK, non_blocking)) {
		fprintf(stderr, "TCP failed to set non-blocking socket\n");
			return -1;
	}

	return sock;
}
