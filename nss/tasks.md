# DOCS

## Debian (Linux)

-   Configure the network in `/etc/network/interfaces`:

    -   Router:
        -   int_net_1
            -   add
                ```
                auto enp0s8
                iface enp0s8 inet static
                    address 192.168.11.1
                    network 192.168.11.0
                    netmask 255.255.255.0
                ```
        -   int_net_2
            -   add
                ```
                auto enp0s9
                iface enp0s8 inet static
                    address 192.168.22.1
                    network 192.168.22.0
                    netmask 255.255.255.0
                ```
    -   Client:
        -   int_net_1
            -   add
                ```
                auto enp0s8
                iface enp0s8 inet static
                    address 192.168.11.11
                    network 192.168.11.0
                    dns-nameservers 192.168.11.1
                    netmask 255.255.255.0
                    gateway 192.168.11.1
                ```
    -   Server:
        -   int_net_2
            -   add
                ```
                auto enp0s8
                iface enp0s8 inet static
                    address 192.168.22.22
                    network 192.168.22.0
                    dns-nameservers 192.168.22.1
                    netmask 255.255.255.0
                    gateway 192.168.22.1
                ```
    -   Other option:
        -   add to /etc/network/interfaces
            ```
            up route add -net 192.168.22.0 netmask 255.255.255.0 gw 192.168.11.1
            up route add -net 192.168.11.0 netmask 255.255.255.0 gw 192.168.22.1
            ```

-   In client

    -   configure the DNS in `/etc/resolv.conf`:
        -   add
            ```
            nameserver 192.168.11.1
            ```
    -   configure PPTP vpn client

        -   install `pptp-linux`
        -   create /etc/ppp/peers/myvpn
            -   add
                ```
                pty "pptp 192.168.22.22 --nolaunchpppd"
                name client1
                password 123
                remotename PPTP
                require-mppe-128
                persist
                maxfail 50
                holdoff 2
                file /etc/ppp/options.pptp
                ipparam myvpn
                ```

    -   configure the wireguard client

        -   install `wireguard`
        -   run `umask 077; wg genkey | tee privatekey | wg pubkey > publickey`
        -   add to `/etc/wireguard/wg0.conf`

            ```
            [Interface]
            Address = 10.0.0.2/24
            PrivateKey = <client_private_key>

            [Peer]
            PublicKey = <server_public_key>
            Endpoint = 192.168.22.22:51820
            AllowedIPs = 0.0.0.0/0
            PersistentKeepalive = 25
            ```

        -   run `wg-quick up wg0`

-   In router

    -   set up the DNS-server

        -   install `bind9`
        -   configure the DNS-server in `/etc/bind/named.conf.local`:
            -   add
                ```
                zone "nss-fh.com" {
                    type master;
                    file "/etc/bind/zones/db.nss-fh.com";
                };
                ```
        -   create the zone file `/etc/bind/zones/db.nss-fh.com`:
            -   add
                ```
                ;
                ; BIND data file for nss-fh.com
                $TTL    604800
                @       IN      SOA     router.nss-fh.com. admin.nss-fh.com. (
                                        2       ; Serial
                                        604800  ; Refresh
                                        86400   ; Retry
                                        2419200 ; Expire
                                        604800 ) ; Negative Cache TTL
                ;
                @       IN      NS      router.nss-fh.com.
                @       IN      A       192.168.22.1
                router  IN      A       192.168.22.1
                www     IN      A       192.168.22.22
                ```

    -   enable IP forwarding in `/etc/sysctl.conf`:
        -   add
            ```
            net.ipv4.ip_forward=1
            ```
    -   set up the firewall

        -   run

            ```
            # sudo iptables -t nat -A PREROUTING -p tcp --dport 80 -j REDIRECT --to-port 443

            sudo iptables -A INPUT -p tcp --dport 80 -j ACCEPT
            sudo iptables -A INPUT -p tcp --dport 443 -j ACCEPT
            sudo iptables -A INPUT -p tcp --dport 53 -j ACCEPT
            sudo iptables -A INPUT -p udp --dport 53 -j ACCEPT
            ```

        -   save the rules
            ```
            sudo iptables-save > /etc/iptables/rules.v4
            ```
        -   load the rules
            ```
            sudo iptables-restore < /etc/iptables/rules.v4
            ```

-   In server

    -   set up web server

        -   install `apache2`
        -   set up a website in `/var/www/html/index.html`
        -   run `sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/server.key -out /etc/ssl/certs/server.crt`
        -   run `sudo a2enmod ssl`
        -   run `sudo a2enmod rewrite`
        -   configure the SSL in `/etc/apache2/sites-available/www.nss-fh.com.conf`:

            -   add

                ```
                <VirtualHost *:443>
                    ServerAdmin admin@nss-fh.com
                    ServerName www.nss-fh.com
                    DocumentRoot /var/www/html

                    SSLEngine on
                    SSLCertificateFile /etc/ssl/certs/server.crt
                    SSLCertificateKeyFile /etc/ssl/private/server.key

                    <Directory /var/www/html>
                        Options Indexes FollowSymLinks
                        AllowOverride All
                        Require all granted
                    </Directory>

                    Header always set Strict-Transport-Security "max-age=31536000; includeSubDomains"

                    ErrorLog ${APACHE_LOG_DIR}/error.log
                    CustomLog ${APACHE_LOG_DIR}/access.log combined
                </VirtualHost>

                <VirtualHost *:80>
                    ServerName www.nss-fh.com
                    Redirect permanent / https://www.nss-fh.com/

                    RewriteEngine On
                    RewriteCond %{HTTPS} off
                    RewriteRule ^/?(.*) https://%{SERVER_NAME}/$1 [R=301,L]
                </VirtualHost>
                ```

        -   enable the site `sudo a2ensite www.nss-fh.com`
        -   disable the default site `sudo a2dissite 000-default`

    -   set up firewall
        -   install `ufw`
        -   run
            ```
            sudo ufw allow http
            sudo ufw allow https
            sudo ufw allow 1723/tcp
            sudo ufw default deny incoming
            sudo ufw default allow outgoing
            sudo ufw enable
            ```
    -   enable IP forwarding in `/etc/sysctl.conf`:
        -   add
            ```
            net.ipv4.ip_forward=1
            ```
    -   set up the PPTP VPN server

        -   install `pptpd`
        -   configure the VPN server in `/etc/pptpd.conf`:
            -   add
                ```
                localip 10.10.0.1
                remoteip 10.10.0.101-200
                ```
        -   configure the VPN options in `/etc/ppp/pptpd-options`:

            -   comment out

                ```
                refuse-pap
                refuse-chap
                refuse-mschap

                ms-dns 10.0.0.1
                ms-dns 10.0.0.2
                ```

        -   configure the VPN users in `/etc/ppp/chap-secrets`:
            -   add
                ```
                client1 pptpd 123 *
                client1 * 123 *
                ```
        -   run `ufw allow 1723/tcp`
        -   run `ufw allow 47`

    -   set up the wireguard VPN server

        -   install `wireguard`
        -   run `umask 077; wg genkey | tee privatekey | wg pubkey > publickey`
        -   add to `/etc/wireguard/wg0.conf`

            ```
            [Interface]
            Address = 10.0.0.1/24
            PrivateKey = <server_private_key>
            ListenPort = 51820
            SaveConfig = true

            [Peer] #client1
            PublicKey = <client_public_key>
            AllowedIPs = 10.0.0.2/32

            [Peer] #client2
            PublicKey = <client_public_key>
            AllowedIPs = 10.0.0.3/32
            ```

        -   run `ufw allow 51820/udp`

## Windows

-   Configure the network:

    -   Router:
        -   int_net_1
            ```
            address: 192.168.111.1
            netmask: 255.255.255.0
            ```
        -   int_net_2
            ```
            address: 192.168.222.1
            netmask: 255.255.255.0
            ```
    -   Client:
        -   int_net_1
            ```
            address: 192.168.111.111
            netmask: 255.255.255.0
            ```
    -   Server:
        -   int_net_2
            ```
            address: 192.168.222.222
            netmask: 255.255.255.0
            ```

-   Enable ICMP echo request in firewall in each machine

-   In client

    -   create the rule to get to int_net_2
        -   `route add 192.168.222.0 mask 255.255.255.0 192.168.111.1 -p`
    -   set preferred DNS server to `192.168.111.1`

-   In router

    -   turn on the IP messages forwarding
        -   in regedit `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Tcpip\Parameters\IPEnableRouter = 1`
    -   set up the DNS server role
        -   create a new zone `nssfh.com`
        -   create hosts with correct ip addresses
            -   `router.nssfh.com` -> `192.168.111.1`
            -   `router.nssfh.com` -> `192.168.222.1`
            -   `www.nssfh.com` -> `192.168.222.222`
            -   `client1.nssfh.com` -> `192.168.111.111`

-   In server

    -   create the rule to get to int_net_1
        -   `route add 192.168.111.0 mask 255.255.255.0 192.168.222.1 -p`
    -   set preferred DNS server to `192.168.222.1`

    -   for web server
        -   install `IIS`
        -   create a new website
            -   bind the website to ip address `All Unassigned` and port `80`
            -   add `index.html` to the website
        -   create a self-signed certificate
        -   bind the certificate to the website ip address `All Unassigned` and port `443`
        -   Configure/HSTS.../Enable

<!-- https://www.transip.eu/knowledgebase/3352-installing-vpn-server-windows-server-2019 -->

-   for wireguard vpn
    -   install wireguard
    -   create a new tunnels with same settings as in linux

        -   for server:

            ```
            [Interface]
            Address = 10.0.0.1/24
            PrivateKey = <server_private_key>
            ListenPort = 51820
            SaveConfig = true

            [Peer] #client1
            PublicKey = <client_public_key>
            AllowedIPs = 10.0.0.2/32

            [Peer] #client2
            PublicKey = <client_public_key>
            AllowedIPs = 10.0.0.3/32
            ```
        - for client:
            ```
            [Interface]
            Address = 10.0.0.2/24
            PrivateKey = <client_private_key>

            [Peer]
            PublicKey = <server_public_key>
            Endpoint = 192.168.22.22:51820
            AllowedIPs = 0.0.0.0/0
            PersistentKeepalive = 25
            ```

    -   activate the tunnels


- for sstp vpn
    - in server
        - install `Remote Access`
        - add features `DirectAccess and VPN (RAS)`
        - deploy `VPN` only
        - configure only VPN
        - add the certificate into `SSL Certificate Binding`
        - add the user vpn:NSSisgreat1

    - in client
        - add new vpn connection
            ```
            VPN provider: Windows (built-in)
            Connection name: SSTP VPN
            Server name: www.nssfh.com
            VPN type: Secure Socket Tunneling Protocol (SSTP)
            Type of sign-in info: User name and password
            User name: vpn
            Password: NSSisgreat1
            ```



# Check of Lab Tasks 2, 3, 4, 5

## lab task 2

### windows

- wait a few minutes and connect to https://www.nssfh.com

    - issued to: `www.nssfh.com`


## lab task 3

### windows

#### sstp vpn

- settings 

- network and internet

- vpn 

- connect to `sstp vpn 2` if connexion is with password, if not create a new connexion with the following settings:

    - VPN provider: Windows (built-in)
    - Connection name: SSTP VPN
    - Server name: www.nssfh.com
    - VPN type: Secure Socket Tunneling Protocol (SSTP)
    - Type of sign-in info: User name and password
    - User name: vpn
    - Password: NSSisgreat1

- ping


#### wireguard vpn

- disconnect from sstp vpn

- search wireguard

- activate the tunnel 

- ping


### linux

#### pptp vpn

- ping 

#### wireguard vpn

- ping

## lab task 4

`./task-4-nss.pdf` 

[here](https://github.com/841723/informatica-s7/blob/35f240003fbe3cab2a9c8d7e0197ceb70813ede2/nss/task-4-nss.pdf)

## lab task 5

### wordpress docker

- open docker desktop app

- `cd task-5`

- `docker compose up`

- open browser and go to [wordpress](http://localhost:8080)
- open browser and go to [phpmyadmin](http://localhost:8282)

### my application docker

change directory to wikiplace

- `code "C:\Users\diego\Desktop\unizar\tfg\wikiplace"`

- `docker compose up`

- open browser and go to [web application](http://localhost)

this will run the Dockerfile in the build/context directory
