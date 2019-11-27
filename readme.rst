Настройка ubuntu
----------------

Рекомендуется использовать Ubuntu 14.04.


Необходимые пакеты
~~~~~~~~~~~~~~~~~~

sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio python python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping libncurses5-dev bison flex bc libelf-dev libsdl1.2-dev mtd-utils dos2unix gettext zip

sudo ln -s /usr/bin/dos2unix /usr/bin/fromdos

Тулчейн
~~~~~~~

wget --no-check-certificate https://releases.linaro.org/components/toolchain/binaries/5.3-2016.05/arm-linux-gnueabihf/gcc-linaro-5.3.1-2016.05-x86_64_arm-linux-gnueabihf.tar.xz

sudo tar xf gcc-linaro-5.3.1-2016.05-x86_64_arm-linux-gnueabihf.tar.xz -C /opt

Прочие настройки
~~~~~~~~~~~~~~~~

Обязательно выполнить:

sudo dpkg-reconfigure dash
Be sure to select "No" when you are asked to use dash as the default system shell. 

Чтобы пароль многократно не запрашивался git и запомнился на час следует выполнить:

git config --global credential.helper 'cache --timeout 3600'


Формирования и компилирования проекта yocto
-------------------------------------------

$ mkdir ~/yocto_varsomam33

$ cd ~/yocto_varsomam33

$ git clone git://arago-project.org/git/projects/oe-layersetup.git tisdk

$ mkdir ~/yocto_varsomam33/tisdk/sources

$ cd ~/yocto_varsomam33/tisdk/sources

$ git clone https://emicon67@bitbucket.org/emicon67/meta-emicon.git

$ cd ~/yocto_varsomam33/tisdk

$ ./oe-layertool-setup.sh -f sources/meta-emicon/meta-variscite-amx3-em/conf/emicon_sdk-01.00.00-config.txt

$ cd ~/yocto_varsomam33/tisdk/build

$ nano conf/local.conf

Change your parallel build and download directory:
Set the build parameters to fully utilize your host machine BB_NUMBER_THREADS = '4'
PARALLEL_MAKE = '-j 6' BB_NUMBER_THREADS should be your host machine's number of threads minus 2 or same. PARALLEL_MAKE should be the number of threads your host machine has plus two.

and add mirrors::

	TI_MIRROR = "http://software-dl.ti.com/processor-sdk-mirror/sources/"
	MIRRORS += " \
		bzr://.*/.*      ${TI_MIRROR} \n \
		cvs://.*/.*      ${TI_MIRROR} \n \
		git://.*/.*      ${TI_MIRROR} \n \
		gitsm://.*/.*    ${TI_MIRROR} \n \
		hg://.*/.*       ${TI_MIRROR} \n \
		osc://.*/.*      ${TI_MIRROR} \n \
		p4://.*/.*       ${TI_MIRROR} \n \
		npm://.*/.*      ${TI_MIRROR} \n \
		ftp://.*/.*      ${TI_MIRROR} \n \
		https?$://.*/.*  ${TI_MIRROR} \n \
		svn://.*/.*      ${TI_MIRROR} \n \
	"

Building the VAR-SOM-AM33 Yocto image

$ cd ~/yocto_varsomam33/tisdk/build

$ export PATH=/opt/gcc-linaro-5.3.1-2016.05-x86_64_arm-linux-gnueabihf/bin:$PATH

$ . conf/setenv

$ MACHINE=ememu bitbake core-image-minimal

Для настоящего ПЛК MACHINE=emcpu47

$ MACHINE=emcpu47 bitbake core-image-minimal

Список доступных образов для отладки:
arago-base-image.bb
arago-console-image.bb
arago-core-tisdk-image.inc  
arago-test-image.bb             
tisdk-rootfs-image.bb               
tisdk-server-rootfs-image.bb
arago-base-tisdk-image.bb  
arago-core-tisdk-image.bb  
arago-image.inc             
tisdk-recovery-rootfs-image.bb  
tisdk-server-extra-rootfs-image.bb

file://variscite-bt.conf 

Путь по которому сбирается rootfs
~/yocto_varsomam33/tisdk/build/arago-tmp-external-linaro-toolchain/work/ememu-linux-gnueabi/core-image-minimal/1.0-r0/rootfs/