///*
 //* ControllerInterface.c
 //*
 //* Created: 2022-05-11 14:17:35
 //*  Author:
 //*/ 
//
//
//// initialize this shit
//
//// in the init:
	//if (pthread_mutex_init(&ioMutex, NULL) != 0) printf("Failed to create ioMutex");
	//
	////Set up serial port
	//serialPort = open("/dev/ttyS0", O_RDWR);
//
	//if (serialPort == -1) printf("Failed to open /dev/ttyS0");
	//
	//tcgetattr(serialPort, &serialSettings);
//
	//fcntl(serialPort, F_SETFL, O_NONBLOCK);
//
	////Set port speed
	//cfsetospeed(&serialSettings, B9600);
	//cfsetispeed(&serialSettings, B9600);
	//
	//serialSettings.c_cflag &= ~CSIZE; 	// Clear char size
	//serialSettings.c_cflag |= CS5;	// set 5 bit char size
	//serialSettings.c_cflag &= ~CSTOPB; // 1 stop bit
	//serialSettings.c_cflag &= ~PARENB; // no parity
	//serialSettings.c_cflag |= CREAD;	// Enable receive
	//serialSettings.c_cc[VMIN] =  1; // Read at least 1 char
	//
	//// remmeber that lights will be in the program so it has to call the program
//void *readSerialPort(void *arg){
	////printf("Started read serial port thread\n");
	//uint8_t data = 0;
	//while (1)
	//{
		//data = 0;
		//
		////Read sent value to data
		//pthread_mutex_lock(&ioMutex);
		//read(serialPort, &data, 1);
		//pthread_mutex_unlock(&ioMutex);
		//
		//if (data == 0b1010) //Both lights red
		//{
			//pthread_mutex_lock(&stateMutex);
			//lights = RED;
			////printf("read port red: %d\n", lights);
			//pthread_mutex_unlock(&stateMutex);
			//print();
			//
		//} else if (data == 0b1001) //North green, south red
		//{
			//pthread_mutex_lock(&stateMutex);
			//lights = NORTHGREEN;
			////printf("read port north green: %d\n", lights);
			//pthread_mutex_unlock(&stateMutex);
			////Allow one car to enter the bridge
			//sem_post(&bridgeEnterSem);
			//
		//} else if (data == 0b0110) //South green, north red
		//{
			//pthread_mutex_lock(&stateMutex);
			//lights = SOUTHGREEN;
			////printf("read port south green: %d\n", lights);
			//pthread_mutex_unlock(&stateMutex);
			////Allow one car to enter the bridge
			//sem_post(&bridgeEnterSem);
			//
		//}
	//}
//}
//
//// need arrival here that does these:
	////write to port
	//uint8_t data = (dir == NORTH) ? 0b0001 : 0b0100;
	//pthread_mutex_lock(&ioMutex);
	//write(serialPort, &data, 1);
	//pthread_mutex_unlock(&ioMutex);