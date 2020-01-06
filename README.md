# xdp-ebpf-sample
Sample code of xdp ebpf using golang as user-space program. using C (obviously) as kernel-space

# Installing bcc iovisor header with tools
```
$ sudo apt-get -y install bison build-essential cmake flex git libedit-dev libllvm6.0 llvm-6.0-dev libclang-6.0-dev python zlib1g-dev libelf-dev luajit luajit-5.1-dev gcc-multilib linux-tools-$(uname -r) linux-headers-$(uname -r) -y && git clone https://github.com/iovisor/bcc.git && mkdir bcc/build; cd bcc/build && cmake .. -DCMAKE_INSTALL_PREFIX=/usr && make && sudo make install && wget https://help.netronome.com/helpdesk/attachments/36025601060 -O bpftool.deb && sudo apt install ./bpftool.deb -y && bpftool version
```

# 1 click go installation
```
# curl https://dl.google.com/go/go1.13.5.linux-amd64.tar.gz -o go1.13.5.linux-amd64.tar.gz  && tar -C /usr/local -xzf go1.13.5.linux-amd64.tar.gz && echo "export PATH=$PATH:/usr/local/go/bin" >> /root/.bashrc && source /root/.bashrc && go version && go get -u github.com/iovisor/gobpf/bcc && go get -u golang.org/x/net/context
```

# Notes
Use ubuntu 18.04 to follow this tutorial because it's fully tested on that version of OS until now