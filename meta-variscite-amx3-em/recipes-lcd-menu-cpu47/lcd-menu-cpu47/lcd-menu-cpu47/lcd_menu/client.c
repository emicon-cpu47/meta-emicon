/*
 * Весь функционал клиентского режима прошивальщика.
 */

void client(bool client_mode);
int get_mask_from_responce(char *data, ssize_t len, char *mask);
void get_new_net_settings(struct sockaddr_in tmp_addr, char *ip, char *gateway);
uint8_t get_mask_bits(char *mask);
int sys_set_ip(char *iface_name, char *ip, char *mask, char *gateway);
int client_tcp_routine (uint32_t srv_s_addr);
void update_fw(void);

/*
 * Точка входа клиентского режима.
 */
void client(bool client_mode)
{
	int bcast_sock;
	struct sockaddr_in srv_addr;
	ssize_t recived_bytes, sent_bytes;
	int sz_addr;
	char buff[BUF_SIZE];
	long int zerro_time;
	long int curent_time;
	char mask[STR_HOST_LEN];
	char new_ip[STR_HOST_LEN];
	char new_gateway[STR_HOST_LEN];
	char str[BUF_SIZE];
	uint8_t mask_bits;

	if (!client_mode)
		return;

	// нужна принудительная смена собственного IP на 254 в конце
	// потому что основной и резервный, если отсутвует МЭК программа
	// могут иметь одинаковый IP и в этом случа синхронизации не будет
	// Сетевые настройки можно брать любые, тк  в дальнейшем их все равно
	// перенастроят на сеть сервера.
	sys_set_ip(NET_NAME, "192.168.254.254", "255.255.255.0", "192.168.254.1");

	bcast_sock = open_nonblock_udp_socket();
	if (bcast_sock <= 0){
		fprintf(stderr, "open socket failed\n");
		return;
	}

	bzero(&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	srv_addr.sin_port = htons(PORT_UDP);

	/*
	 * клиенту тоже нужно завязать сокет, потому как тответ от сервера
	 * будет широковещательным, чтобы пройти разные подсети.
	 */
	if (bind(bcast_sock, (struct sockaddr *)&srv_addr,
	    sizeof(srv_addr)) != 0) {
	    	fprintf(stderr, "bind socket failed\n");
	    	close(bcast_sock);
	    	bcast_sock = 0;
		return;
	}


	lcd_puts(MENU_SYNC_SCREEN, 0, 0, "App Sync");
	lcd_puts(MENU_SYNC_SCREEN, 1, 0, "Started ");
	// system("killall codesyscontrol");
	sleep(3);

	sent_bytes = sendto(bcast_sock, REQUEST_FW_SERVER,
		    sizeof(REQUEST_FW_SERVER), 0,
		    (struct sockaddr *)&srv_addr,
		    sizeof(struct sockaddr));

	if (sent_bytes > 0){
		fprintf(stderr, "REQUEST_FW_SERVER is sent\n");
		lcd_puts(MENU_SYNC_SCREEN, 0, 0, "Finding ");
		lcd_puts(MENU_SYNC_SCREEN, 1, 0, "Server  ");
	}

	usleep(1000);
	sz_addr = sizeof(srv_addr);
	bzero(&srv_addr, sz_addr);

	// читаем циклом ограниченным по времени
	zerro_time = get_curent_time();
	curent_time = zerro_time;

	while (curent_time - zerro_time < TIMEOUT_READING_UDP) {
		recived_bytes = recvfrom(bcast_sock, buff, BUF_SIZE, 0,
					 (struct sockaddr *)&srv_addr,
					 &sz_addr);

		if (get_mask_from_responce(buff, recived_bytes, mask)) {
			close(bcast_sock);
			// получили маску сервера, теперь расчитываем IP
			// и gateway.
			get_new_net_settings(srv_addr, new_ip, new_gateway);

			fprintf(stderr, "ip:%s mask:%s gateway: %s\n",
				new_ip, mask, new_gateway);
			// прописываем новые сетевые параметры
			mask_bits = get_mask_bits(mask);

			// strcpy(str, NETWORK_UPDATE_SCRIPT);
			// strcat(str, " ");
			// strcat(str, inet_ntoa(srv_addr.sin_addr));
			// strcat(str, " ");
			// // strcat(str, mask_bits);
			// sprintf(str, "%s %d", str, mask_bits);
			// strcat(str, " ");
			// strcat(str, new_gateway);
			sprintf(str, "%s %s %d %s",
				NETWORK_UPDATE_SCRIPT,
				inet_ntoa(srv_addr.sin_addr),
				mask_bits,
				new_gateway);
			fprintf(stderr, "SYSTEM: %s\n", str);
			system(str);

			sys_set_ip(NET_NAME, new_ip, mask, new_gateway);
			// новые сетевые параметры установлены переходим на TCP
			// при успешном получении прошивки ЦПУ перегрузится
			client_tcp_routine(srv_addr.sin_addr.s_addr);
			fprintf(stderr, "Выход client_tcp_routine\n");
			return;
		}

		curent_time = get_curent_time();
	}


	usleep(500000);
	close(bcast_sock);
}

/*
 * Отделяет информацию о МАСКЕ сети в виде строки из ответа сервера.
 */
int get_mask_from_responce(char *data, ssize_t len, char *mask)
{

	ssize_t str_len;
	char buff[BUF_SIZE];
	struct in_addr srv_mask;

	str_len = strlen(RESPOND_FW_SERVER);

	if (len > str_len) {
		// выделяем и сравниваем заголовок
		memcpy(buff, data, str_len);
		buff[str_len] = '\0';
		if (!strcasecmp(buff, RESPOND_FW_SERVER)) {
			// заголовок совпал, отдаем маску
			memcpy(buff, data + str_len, len - str_len);
			buff[len - str_len] = '\0';

			if (inet_aton(buff, &srv_mask)) {
				strcpy(mask, buff);
				return 1;
			}
		}
	}

	return 0;
}

/*
 * Вовращает новые параметры сети для клиента соглано параметрам сети сервера.
 * Попросту последний байт IP сервера меняет на зарезервированный и также меняет
 * Gateway.
 */
void get_new_net_settings(struct sockaddr_in tmp_addr, char *ip, char *gateway)
{
	union ip_union {
		unsigned long s_addr; 
		uint8_t bytes[4];
	} ip_union;

	ip_union.s_addr = tmp_addr.sin_addr.s_addr;
	ip_union.bytes[3] = 254;
	tmp_addr.sin_addr.s_addr = ip_union.s_addr;
	strcpy(ip, inet_ntoa(tmp_addr.sin_addr));
	ip_union.bytes[3] = 1;
	tmp_addr.sin_addr.s_addr = ip_union.s_addr;
	strcpy(gateway, inet_ntoa(tmp_addr.sin_addr));
}

/*
 * Возвращает количесто единиц в маске.
 */
uint8_t get_mask_bits(char *mask)
{
	uint32_t n;
	uint32_t n_mask = 1;
	uint8_t bits = 0;

		inet_pton(AF_INET, mask, &n);
	while (n > 0) {
		if (n & n_mask)
			bits++;
		n = n >> 1;
	}

	return bits;
}

/*
 * Устанавливает параметры сети системными вызовами.
 */
int sys_set_ip(char *iface_name, char *ip, char *mask, char *gateway)
{
	uint8_t bits;
	char str[100];

	bits = get_mask_bits(mask);

	sprintf(str, "ip addr flush dev %s", iface_name);
	//fprintf(stderr, "%s\n", str);
	system(str);

	sprintf(str, "ip addr add %s/%d dev %s", ip, bits, iface_name);
	//fprintf(stderr, "%s\n", str);
	system(str);

	sprintf(str, "ip route add default via %s", gateway);
	//fprintf(stderr, "%s\n", str);
	system(str);

	return 0;
}

/*
 * Производит прием прошивки по TCP.
 */
int client_tcp_routine (uint32_t srv_s_addr)
{
	int sock;
	struct sockaddr_in addr;
	int non_blocking = 1;
	char buff[BUF_SIZE];
	int fd;
	ssize_t recived_bytes;
	bool file_received = false;
	struct timeval tv;
	int i;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1) {
		fprintf(stderr, "TCP сокет НЕ создан!\n");
		return -1;
	}

	tv.tv_sec = 2;
	tv.tv_usec = 0;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

	fprintf(stderr, "TCP client sock: %d\n", sock);
	// if (-1 == fcntl(sock, F_SETFL, O_NONBLOCK, non_blocking)) {
	//     fprintf(stderr, "TCP failed to set non-blocking socket\n" );
	//     close(sock);
	//     return -1;
	// }

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_TCP);
	addr.sin_addr.s_addr = srv_s_addr;
	fprintf(stderr, "try TCP connect to: %s\n", inet_ntoa(addr.sin_addr));

	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("TCP/IP connection failed");
		close(sock);
		return -1;
	}

	send(sock, REQUEST_FW, sizeof(REQUEST_FW), 0);

	// переходим на прием
	
	fd = open(FW_FILE_RECEIVED, O_WRONLY | O_CREAT, 0666);
	if (fd == -1){
		fprintf(stdout, "Принимающий файл НЕ открылся!\n");
		close(sock);
		return -1;
	} else {
		fprintf(stderr, "Принимающий файл открылся\n");
	}
	
	lcd_puts(MENU_SYNC_SCREEN, 0, 0, "App Sync");
	lcd_puts(MENU_SYNC_SCREEN, 1, 0, "Running ");

	fprintf(stderr, "Переходим к чтению. Флаг: %d\n", file_received);
	i = 0;
	while (!file_received) {
		
		recived_bytes = recv(sock, buff, BUF_SIZE, 0);
		if (recived_bytes > 0) {
			if (recived_bytes == sizeof(EOF_STR)
			    && !strcasecmp(buff, EOF_STR)) {
				// конец файла
				close (fd);
				fd = 0;
				close (sock);
				fprintf(stdout, "\nFW Прием прошивки окончен.\n");
				file_received = true;
			} else {
				i++;
				fprintf(stdout, "i %d - %ld \n", i, recived_bytes);
				write(fd, buff, recived_bytes);
			}
		}
	}

	if (file_received)
		update_fw(); // перегрузит ЦПУ

	fprintf(stderr, "выход 0\n");
	return 0;
}

/*
 * Обновляет прошивку. Системным вызовом исполняется внешинй скрипт, который
 * обновит полученную прошивку и перезагрузит ЦПУ.
 */
void update_fw(void)
{
	// lcd_puts(MENU_SYNC_SCREEN, 0, 0, "Sync OK ");
	// lcd_puts(MENU_SYNC_SCREEN, 1, 0, "Reboot  ");
	fprintf(stderr, "update_fw\n");

	system(FW_UPDATE_SCRIPT);
	exit(1);
}

