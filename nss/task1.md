# Task 1

## Debian (Linux)

- Configure the network in `/etc/network/interfaces`:
    - Router: 
        - int_net_1
            - add 
                ```
                auto enp0s8
                iface enp0s8 inet static
                    address 192.168.11.1
                    network 192.168.11.0
                    netmask 255.255.255.0
                ```
        - int_net_2
            - add 
                ```
                auto enp0s9
                iface enp0s8 inet static
                    address 192.168.22.1
                    network 192.168.22.0
                    netmask 255.255.255.0
                ```
    - Client:
        - int_net_1
            - add 
                ```
                auto enp0s8
                iface enp0s8 inet static
                    address 192.168.11.11
                    network 192.168.11.0
                    netmask 255.255.255.0
                ```
    - Server:
        - int_net_2
            - add 
                ```
                auto enp0s8
                iface enp0s8 inet static
                    address 192.168.22.22
                    network 192.168.22.0
                    netmask 255.255.255.0
                ```



## Windows

- Configure the network:
    - Router: 
        - int_net_1
            ```
            address: 192.168.111.1 
            netmask: 255.255.255.0
            ```
        - int_net_2
            ```
            address: 192.168.222.1
            netmask: 255.255.255.0
            ```
    - Client:
        - int_net_1
            ```
            address: 192.168.111.111
            netmask: 255.255.255.0
            ```
    - Server:
        - int_net_2
            ```
            address: 192.168.222.222
            netmask: 255.255.255.0
            ```

- Enable ICMP echo request in firewall in each machine
