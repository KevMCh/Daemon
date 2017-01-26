# Operating System Daemon

### Inotify

Daemon that implements inotify.

Inotify is a Linux kernel subsystem that acts to notice changes to the filesystems, and report those changes to applications.

### Installation

To install the inotify service with the server:

    git clone https://github.com/KevMCh/Daemon

    cd /Daemon/Vagrant/data

    sudo make installInotifyServer

### Usage

Start the inotify service:

    service observer start directory ipserver port

Start the sneak service:

    service sneak Start

Stop whatever service:

    service nameservice stop

The result of the inotify functionality are available in the logs file of server.

    sudo tail -f /var/log/syslog
