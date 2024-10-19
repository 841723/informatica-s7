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
                zone "nss.com" {
                    type master;
                    file "/etc/bind/zones/db.nss.com";
                };
                ```
        - create the zone file `/etc/bind/zones/db.nss.com`:
            - add
                ```
                ;
                ; BIND data file for nss.com
                $TTL    604800
                @       IN      SOA     router.nss.com. admin.nss.com. (
                                        2       ; Serial
                                        604800  ; Refresh
                                        86400   ; Retry
                                        2419200 ; Expire
                                        604800 ) ; Negative Cache TTL
                ;
                @       IN      NS      router.nss.com.
                @       IN      A       192.168.22.1
                router  IN      A       192.168.22.1
                www     IN      A       192.168.22.22
                ```

    - enable IP forwarding in `/etc/sysctl.conf`:
        -   add
            ```
            net.ipv4.ip_forward=1
            ```

- In server, 
    - install ```apache2```
    - run ```sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/server.key -out /etc/ssl/certs/server.crt```
    - run ```sudo a2enmod ssl```
    - configure the SSL in `/etc/apache2/sites-available/www.nss-fh.com.conf`:
        - 
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
            ```
    - enable the site ```sudo a2ensite www.nss-fh.com```
    - disable the default site ```sudo a2dissite 000-default```
    - configure the redirect in `/etc/apache2/sites-available/000-default.conf`:
        - add
            ```
            <VirtualHost *:80>
                ServerName www.nss-fh.com
                Redirect permanent / https://www.nss-fh.com/
            </VirtualHost>
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
