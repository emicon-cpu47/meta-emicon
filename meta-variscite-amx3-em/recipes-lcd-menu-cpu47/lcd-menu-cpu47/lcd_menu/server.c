/*
 * Весь функционал серверного режима прошивальщика.
 */

void server(bool server_mode);
int get_mask(char *net_name, char *mask_buff);
void send_mask(int bcast_sock);
int server_tcp_routine(int listener);
void send_fw(int sock);

void server(bool server_mode)
{
	static int bcast_sock = 0;
	static int sock = 0;
	static int listener = 0;
	struct sockaddr_in srv_addr;
	struct  sockaddr_in cl_addr;
	int sz_addr;
	char buff[BUF_SIZE];
	ssize_t recived_bytes;
	struct sockaddr_in tcp_addr;

	if (!server_mode){
		if (bcast_sock != 0){
			close(bcast_sock);
			bcast_sock = 0;
		}
		if (listener != 0){
			fprintf(stderr, "close TCP socket: %d\n", listener);
			close(listener);
			listener = 0;
		}
		if (bcast_sock != 0){
			close(sock);
			sock = 0;
		}

		return;
	}

	if (bcast_sock == 0) {
		bcast_sock = open_nonblock_udp_socket();
		if (bcast_sock <= 0){
			fprintf(stderr, "open socket failed\n");
			bcast_sock = 0;
			return;
		}

		bzero(&srv_addr, sizeof(srv_addr));
		srv_addr.sin_family = AF_INET;
		srv_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
		srv_addr.sin_port = htons(PORT_UDP);

		if (bind(bcast_sock, (struct sockaddr *)&srv_addr,
		    sizeof(srv_addr)) != 0) {
		    	fprintf(stderr, "bind socket failed\n");
		    	close(bcast_sock);
		    	bcast_sock = 0;
			return;
		}
	}

	if (listener == 0) {
		listener = open_nonblock_tcp_socket();
		
		tcp_addr.sin_family = AF_INET;
		tcp_addr.sin_port = htons(PORT_TCP);
		tcp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		if(bind(listener, (struct sockaddr *)&tcp_addr,
			sizeof(tcp_addr)) < 0) {
			fprintf(stderr, "bind TCP socket failed\n");
			close(listener);
			return;
		}

		listen(listener, 1);
		fprintf(stderr, "TCP socket %d open\n", listener);

	}

	sz_addr = sizeof(cl_addr);
	bzero(&cl_addr, sz_addr);

	recived_bytes = recvfrom(bcast_sock, buff, BUF_SIZE, 0,
				     (struct sockaddr *)&cl_addr, &sz_addr);

	if (recived_bytes > 0) {
		if (!strcasecmp(buff, REQUEST_FW_SERVER)) {
		
			fprintf(stdout, "get request NET from %s\n",
				inet_ntoa(cl_addr.sin_addr));
			// пришел запрос на поиск сервера - отсылаем ответ
			send_mask(bcast_sock);
			close(bcast_sock);
			bcast_sock = 0;
		}

	}

	server_tcp_routine(listener);

	return;
}

void send_mask(int bcast_sock)
{
	char buff[BUF_SIZE];
	ssize_t sent_bytes;
	char mask[STR_HOST_LEN];
	struct  sockaddr_in cl_addr;

	strcpy(buff, RESPOND_FW_SERVER);
	get_mask(NET_NAME, mask);
	strcat(buff, mask);
	fprintf(stderr, "Net MASK: %s\n", mask);

	bzero(&cl_addr, sizeof(cl_addr));
	cl_addr.sin_family = AF_INET;
	cl_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	cl_addr.sin_port = htons(PORT_UDP);

	sent_bytes = sendto(bcast_sock, buff, strlen(buff) + 1, 0,
	       (struct sockaddr *)&cl_addr, sizeof(struct sockaddr));
	if (sent_bytes > 0)
		fprintf(stderr, "send mask\n");

}


int get_mask(char *net_name, char *mask_buff)
{
	struct ifaddrs *ifaddr, *ifa;
	int res;
	char host[NI_MAXHOST];
	char mask[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		fprintf(stderr, "getifaddrs failed\n");
		return -1;
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;  

		res = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
				  host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		res = getnameinfo(ifa->ifa_netmask, sizeof(struct sockaddr_in),
				  mask, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, net_name) == 0)
		    &&(ifa->ifa_addr->sa_family == AF_INET)) {
			if (res != 0) {
				fprintf(stderr, "getnameinfo failed: %s\n",
					gai_strerror(res));
				return -1;
			}
			strcpy(mask_buff, mask);
		}
	}

	freeifaddrs(ifaddr);
	return 0;
}

int server_tcp_routine(int listener)
{
	int sock;
	char buff[BUF_SIZE];
	int bytes_read;
	long int zerro_time;
	long int curent_time;
	struct timeval tv;

	zerro_time = get_curent_time();
	curent_time = zerro_time;
	
	sock = accept(listener, NULL, NULL);
	//fprintf(stderr, "TCP sock %d\n", sock);

	if(sock > 0) {
		// есть в очереди клиент, утсанавливаем на его сокет
		//таймаут и ждем данных.
		tv.tv_sec = TIMEOUT_READING_TCP / 1000; 
		tv.tv_usec = 0;
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,
			   sizeof tv);

		bytes_read = recv(sock, buff, BUF_SIZE, 0);
		if(bytes_read > 0){
			// определяем тип запроса и выдаем соответвующий
			// ответ
			if (!strcasecmp(buff, REQUEST_FW))
				send_fw(sock);
		}

		close(sock);
	}


	return 0;
}

void send_fw(int sock)
{
	ssize_t file_length;
	int fd;
	int sent_bytes, ret_in;
	char buff[BUF_SIZE];
	ssize_t i_sent_bytes = 0;
	int i;
	int res;

	fprintf(stderr, "Готовимся отправить прошивку\n");

	// создаем прошивку внешним скриптом
	system(FW_CREATE_SCRIPT);
	// ждем таймаут
	sleep(1);

	fprintf(stderr, "Прошивка создана.\n");

	fd = open(FW_FILE, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Файл прошивки НЕ открылся!\n");
		return;
	}
	i = 0;
	while ((ret_in = read(fd, &buff, BUF_SIZE)) > 0) {
		// TODO при потере клиента отправка убивает процесс!
		i++;
		res = send(sock, buff, ret_in, 0);
		if (res < 0){
			fprintf(stderr, "Передача прошивки оборвана.\n");
			close(fd);
			return;
		}

		i_sent_bytes += ret_in;
		fprintf(stderr, "i %d i_sent_bytes %ld, %d\n", i, i_sent_bytes, ret_in);
		usleep(10000);
	}

	// передаем конец файла
	sent_bytes = send(sock, EOF_STR, sizeof(EOF_STR), 0);

	if (sent_bytes > 0)
		fprintf(stderr, "Send EOF %d\n", sent_bytes);
	else
		fprintf(stderr, "ERROR send EOF %d\n", sent_bytes);

	fprintf(stderr, "Передача прошивки завершена.\n");
	
	close(fd);

	return;
}
