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

- In client, configure the DNS in `/etc/resolv.conf`:
    -   add
        ```
        nameserver 192.168.11.1
        ```

-   In router
    - set up the DNS-server
        - install ```bind9```
        - configure the DNS-server in `/etc/bind/named.conf.local`:
            - add
                ```
                zone "nss-fh.com" {
                    type master;
                    file "/etc/bind/zones/db.nss-fh.com";
                };
                ```
        - create the zone file `/etc/bind/zones/db.nss-fh.com`:
            - add
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

    - enable IP forwarding in `/etc/sysctl.conf`:
        -   add
            ```
            net.ipv4.ip_forward=1
            ```
    - set up the firewall
        - run
            ```
            # sudo iptables -t nat -A PREROUTING -p tcp --dport 80 -j REDIRECT --to-port 443

            sudo iptables -A INPUT -p tcp --dport 80 -j ACCEPT
            sudo iptables -A INPUT -p tcp --dport 443 -j ACCEPT
            sudo iptables -A INPUT -p tcp --dport 53 -j ACCEPT
            sudo iptables -A INPUT -p udp --dport 53 -j ACCEPT
            ```
        - save the rules
            ```
            sudo iptables-save > /etc/iptables/rules.v4
            ```
        - load the rules
            ```
            sudo iptables-restore < /etc/iptables/rules.v4
            ``` 

- In server, 
    - set up web server
        - install ```apache2```        
        - set up a website in ```/var/www/html/index.html```        
        - run ```sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/server.key -out /etc/ssl/certs/server.crt```        
        - run ```sudo a2enmod ssl```        
        - run ```sudo a2enmod rewrite```        
        - configure the SSL in ```/etc/apache2/sites-available/www.nss-fh.com.conf```:
            - add
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
        - enable the site ```sudo a2ensite www.nss-fh.com```
        - disable the default site ```sudo a2dissite 000-default```

    - set up firewall
        - install ```ufw```
        - run 
            ```
            sudo ufw allow http 
            sudo ufw allow https
            sudo ufw allow 1723/tcp
            sudo ufw default deny incoming
            sudo ufw default allow outgoing
            sudo ufw enable
            ```
    - set up the PPTP VPN server
        - install ```pptpd```
        - configure the VPN server in ```/etc/pptpd.conf```:
            - add
                ```
                localip localip 192.168.22.22
                remoteip 192.168.22.10-20
                ```
        - configure the VPN options in ```/etc/ppp/pptpd-options```:
            - as default
        - configure the VPN users in ```/etc/ppp/chap-secrets```:
            - add
                ```
                user1 pptpd password1 *
                ```
        - enable IP forwarding in ```/etc/sysctl.conf```:
            - add
                ```
                net.ipv4.ip_forward=1
                ```


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
