sudo apt-get update
sudo apt-get install build-essential     
sudo apt-get install libncurses5-dev      
sudo apt-get install libssl-dev   
sudo apt-get install m4    
sudo apt-get install unixodbc unixodbc-dev   
sudo apt-get install freeglut3-dev libwxgtk2.8-dev     
sudo apt-get install xsltproc     
sudo apt-get install fop    
sudo apt-get install tk8.5   
wget http://www.erlang.org/download/otp_src_17.5.tar.gz
tar zxvf otp_src_17.5.tar.gz   
cd /home/......

./configure --prefix=/home/erlang --without-wx --without-javac
make && make install  
Add the line into bashrc:
    PATH=$PATH:/home/erlang/bin
