
![Alt text](https://github.com/LEAD-Anoy74/ZeroClassic/blob/master/art/zero_icon.png?raw=true "ZeroClassic")

[ZERC](https://github.com/LEAD-Anoy74/ZeroClassic) is a fork of ZeroCurrency and Zero.
Zero is a fork of Bitcoin that adds shielded transaction via zk-SNARKs.

This software is the ZERO Classic node. It downloads and stores the entire history of ZERO Classic transactions, about 1GB at this point.
Depending on the speed of your computer and network connection, the synchronization process could take several hours.

Announcements
-----------------
On September 15th, the old ZERO will fork to add block halving and dev fees. This means that a % of the Zero block reward, will go straight into the devs wallets. We've dediced to NOT SUPPORT THIS UPDATE and continue maintaining the old fashioned Zero like it should be. Free, open source, without any fee. This is why ZERO Classic (ZERC) is born.

What should I do if I already own some coins?
-----------------
Zero will then have two chains:
- MAIN CHAIN --> the one for users who will update their wallet and support dev fees
- OUR OLD FASHIONED CHAIN --> for who decided to keep their wallet as it was

Coins existing on the initial chain, before 15th of September, will continue to exists in both chains. Then, every fork will continue on his own. Even your receiving adresses.

Security Warnings
-----------------
See important security warnings on the
[Security Information page](https://z.cash/support/security/).

**ZERO Classic is unfinished and highly experimental.** Use at your own risk.

Deprecation Policy
------------------
This release is considered deprecated 26 weeks after the release day. There
is an automatic deprecation shutdown feature which will halt the node some
time after this 26 week time period. The automatic feature is based on block
height and can be explicitly disabled.

Building (16.04.5 LTS (Xenial Xerus))
--------
Currently only Linux build is officially supported.  8GB RAM is recommended.

### Install packages (needs to be done only once)
```
sudo apt-get install build-essential pkg-config libc6-dev m4 g++-multilib autoconf libtool ncurses-dev unzip git python python-zmq   zlib1g-dev wget bsdmainutils automake cmake
```

### Download cryptographic keys (needs to be done only once)
```
./zcutil/fetch-params.sh
```

### Obtain the ZERO Classic software from GitHub
```
git clone https://github.com/LEAD-Anoy74/ZeroClassic/
cd ZeroClassic
git checkout master
```

### Build the source code to produce binary executables:
```
cd ZeroClassic
chmod +x src/leveldb/build_detect_platform zcutil/build.sh zcutil/fetch-params.sh depends/config.guess depends/config.sub autogen.sh share/genbuild.sh 
./zcutil/fetch-params.sh
./zcutil/build.sh --disable-rust -j$(nproc)
```
On a typical laptop -j3 works fine, while retaining some UI interactivity
```
./zcutil/build.sh --disable-rust -j3
```

### Create a ZERO Classic configuration file
```
mkdir -p ~/.zero
echo "rpcuser=YOUR_USER" > ~/.zero/zero.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >> ~/.zero/zero.conf
echo "rpcport=23800" >> ~/.zero/zero.conf
echo "addnode=163.172.49.214" >> ~/.zero/zero.conf
echo "addnode=95.179.141.123" >> ~/.zero/zero.conf
echo "addnode=173.249.40.205" >> ~/.zero/zero.conf
echo "addnode=149.56.97.170" >> ~/.zero/zero.conf
```

### Seeder Nodes
As of 05/12/2018 the following seeder nodes are up and run a recent Linux version:
```
addnode=163.172.49.214
addnode=95.179.141.123
addnode=173.249.40.205
addnode=149.56.97.170
```

### Enable CPU mining (optional)
```
echo 'gen=1' >> ~/.zero/zero.conf
echo "genproclimit=1" >> ~/.zero/zero.conf
echo 'equihashsolver=tromp' >> ~/.zero/zero.conf
```

A sample of the current zero.conf
```
./contrib/zero.conf
```
A sample demonstrating a large number of command line options
```
./contrib/debian/examples/zero.conf
```

Running & Using ZERO Classic
--------------------
After a successful build ZERO Classic binaries are in `./src`. The two important binaries are `zerod` and `zero-cli`.

Your wallet will be created (on first zerod run) in: ~/.zero/wallet.zero
Please backup your wallet often and keep it safe.

The usage is currently the same ZCash. For more information see the [ZCash User Guide](https://github.com/zero/zero/wiki/1.0-User-Guide#running-zero).
