# Debian (Linux)

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
    - Other option:
        - add to /etc/network/interfaces
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

        -   create /etc/ppp/peers/pptpserver
            -   add
                ```
                pty "pptp www.nss-fh.com --nolaunchpppd"
                name client1
                password password1
                remotename PPTP
                require-mppe-128
                refuse-eap
                refuse-pap
                refuse-chap
                refuse-mschap
                require-mschap-v2
                persist
                noauth
                ```

    -   configure the openvpn client

        -   create `client.ovpn`

            -   add
                ```
                client
                dev tun
                proto udp
                remote www.nss-fh.com 1194
                resolv-retry infinite
                nobind
                persist-key
                persist-tun
                auth-user-pass
                tls-auth /etc/openvpn/ta.key 1
                remote-cert-tls server
                verb 3
                ```

        -   run `openvpn --genkey secret /etc/openvpn/ta.key`
        -   run `sudo openvpn --config client.ovpn`

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
    -   set up the PPTP VPN server
        -   install `pptpd`
        -   configure the VPN server in `/etc/pptpd.conf`:
            -   add
                ```
                localip localip 192.168.22.22
                remoteip 192.168.22.10-20
                ```
        -   configure the VPN options in `/etc/ppp/pptpd-options`:
            -   add
                ```
                noauth
                ```
        -   configure the VPN users in `/etc/ppp/chap-secrets`:
            -   add
                ```
                user1 pptpd password1 *
                ```
        -   enable IP forwarding in `/etc/sysctl.conf`:
            -   add
                ```
                net.ipv4.ip_forward=1
                ```
    -   set up the openvpn VPN server

        -   install `openvpn` and `easy-rsa`
        -   run `make-cadir ~/openvpn-ca`
        -   run
            ```
            ./easyrsa init-pki
            ./easyrsa build-ca
            ./easyrsa build-server-full server
            ./easyrsa gen-dh
            openvpn --genkey secret ta.key
            ./easyrsa build-client-full client1
            ```
        -   set up `/etc/openvpn/server.conf`

            -   add

                ```
                port 1194
                proto udp
                dev tun
                ca /etc/openvpn/ca.crt
                cert /etc/openvpn/server.crt
                key /etc/openvpn/server.key
                dh /etc/openvpn/dh.pem
                tls-auth /etc/openvpn/ta.key 0
                server 10.8.0.0 255.255.255.0
                ifconfig-pool-persist ipp.txt
                push "redirect-gateway def1 bypass-dhcp"
                push "dhcp-option DNS 8.8.8.8"
                keepalive 10 120
                cipher AES-256-CBC
                persist-key
                persist-tun
                status openvpn-status.log
                verb 3

                plugin /usr/lib/openvpn/openvpn-plugin-auth-pam.so login

                verify-client-cert none
                username-as-common-name
                ```

        -   add user `vpnuser:vpn`

# Windows

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
        - `route add 192.168.222.0 mask 255.255.255.0 192.168.111.1 -p`
    - set preferred DNS server to `192.168.111.1`

-   In router
    -   turn on the IP messages forwarding
        -   in regedit `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Tcpip\Parameters\IPEnableRouter = 1`
    -   set up the DNS server role
        - create a new zone `nssfh.com`
        - create hosts with correct ip addresses
            - `router.nssfh.com` -> `192.168.111.1`
            - `router.nssfh.com` -> `192.168.222.1`
            - `www.nssfh.com` -> `192.168.222.222`
            - `client1.nssfh.com` -> `192.168.111.111`
        

-   In server
    -   create the rule to get to int_net_1
        -   `route add 192.168.111.0 mask 255.255.255.0 192.168.222.1 -p`
    - set preferred DNS server to `192.168.222.1`
    
    - for web server
        - install `IIS`
        - create a new website
            - bind the website to ip address `All Unassigned` and port `80`
            - add `index.html` to the website
        - create a self-signed certificate
        - bind the certificate to the website ip address `All Unassigned` and port `443` 
        - Configure/HSTS.../Enable


https://www.transip.eu/knowledgebase/3352-installing-vpn-server-windows-server-2019#:~:text=Click%20the%20Windows%20Start%20button%20and%20the%20Settings%20icon.&text=Then%20click%20on%20'Network%20%26%20Internet'.&text=Click%20on%20'VPN'%20on%20the,'Add%20a%20VPN%20connection'.&text=Enter%20the%20details%20on%20the,VPN%20connection'%20screen%20that%20appears.