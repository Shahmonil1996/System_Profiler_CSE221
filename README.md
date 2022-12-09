# System_Profiler_CSE221

Requirements:
1. WSL
2. VSCode

Codes run on Windows system from VS Code :
1. CPU - Function_Overheads.c
2. CPU - getpid.c
3. CPU - loop_overhead.c
4. CPU - new_process_cmd.c and new_process_cmd.h
5. CPU - rdtsc.c
6. CPU - thread.c 
7. CPU - context_switch.c 
8. CPU - context_switch_thread.c

Codes run on remote WSL in VS Code
1. File - contention_final.c
2. File - file_cache_size_final.c
3. File - file_read_final.c
4. Network - ping_in_icmp.c 
5. Network - ping_in_tcp_client.c 
6. Network - ping_in_tcp_server.c 
7. Network - tcp_client_startup_and_tear_down.c
8. Network - ping_in_tcp_server_remote.c
9. Memory - cache_size_final.c
10. Memory - memory_bw.c 
11. Memory - page_fault_minor.c (Minor Fault)
12. Memory - page-fault_major.c (Major fault)


VS code for windows : Compiler used VS Code
VS code files added in the github repository
Prerequisities:
To run the commands in windows, we had to move all background processes to a core which we are not using , by using the "setAffinity" utility in Task Manager. 

Run commands :
Function_Overheads.c : 
-----------------------
Build Command : gcc.exe src/CPU/Function_Overheads.c -o src/CPU/Function_Overheads.exe
Run Command : ./src/CPU/Function_Overheads.exe

getpid.c:
----------
Build Command : gcc.exe src/CPU/getpid.c -o src/CPU/getpid.exe
Run Command : ./src/CPU/getpid.exe

loop_overhead.c:
--------------------
Build Command : gcc.exe src/CPU/loop_overhead.c -o src/CPU/loop_overhead.exe
Run Command : ./src/CPU/loop_overhead.exe

new_process_cmd.c:
-------------------
Build Command : gcc.exe src/CPU/new_process_cmd.c -o src/CPU/new_process_cmd.exe
Run Command : ./src/CPU/new_process_cmd.exe

rdtsc.c:
---------
Build Command : gcc.exe src/CPU/rdtsc.c -o src/CPU/rdtsc.exe
Run Command : ./src/CPU/rdtsc.exe

thread.c 
----------
Build Command : gcc.exe src/CPU/thread.c -o src/CPU/thread.exe
Run Command : ./src/CPU/thread.exe

context_switch.c:
------------------
Build Command : gcc.exe src/CPU/context_switch.c -o src/CPU/context_switch.exe
Run Command : ./src/CPU/context_switch.exe

context_switch_thread.c:
------------------
Build Command : gcc.exe src/CPU/context_switch_thread.c -o src/CPU/context_switch_thread.exe
Run Command : ./src/CPU/context_switch_thread.exe


WSL on VS Code:
Compiler Used : gcc
 
contention_final.c:
---------------------
Build Command : gcc-9  -g src/File/contention_final.c -o src/File/contention_final	
Run Command : (can vary num processes from 1 to 30.. Sudo needed to flush cache
sudo ./src/File/contention_final <num_processes>

file_cache_size_final.c:
-------------------------
Build Command : gcc-9  -g src/File/file_cache_size_final.c -o src/File/file_cache_size_final
Run Command : (We downloaded the 10GB binary file from : https://testfiledownload.com/)
sudo ./src/File/file_cache_size_final 10GB.bin

file_read_final.c :
------------------- 
Prerequisities : 
1. Local Mode:
	1.1 Created files with names and sizes as the name of the file : "log1mb","log2mb","log4mb","log8mb","log16mb","log32mb","log64mb","log128mb"
2. Remote mode :
	2.1 Mounted remote file path using : sudo sshfs -o allow_other,IdentityFile=/home/monils/.ssh/id_rsa.pub  <username>@ieng6-ece-20.ucsd.edu:<remote_dir_path> /mnt/remote_dir
	2.2 Created files with names and sizes as the name of the file : "log8kb","log16kb","log32kb","log64kb","log128kb","log256kb","log512kb","log1mb"
	
Build command : gcc-9  -g src/File/file_read_final.c -o src/File/file_read_final
Run Commands : 
sudo ./src/File/file_read_final 0 (Local)
sudo ./src/File/file_read_final 1 (Remote)


cache_size_final.c:
------------------- 
Build Command : 	gcc-9  -g src/Memory/cache_size_final.c -o src/Memory/cache_size_final -D _GNU_SOURCE
Run Command : ./src/Memory/cache_size_final

memory_bw.c:
------------
Build Command : gcc-9  -g src/Memory/memory_bw.c -o src/Memory/memory_bw -D _GNU_SOURCE

Run Command : ./src/Memory/memory_bw

page_fault_minor.c (Minor):
--------------
Build Command: gcc-9  -g src/Memory/page_fault_minor.c -o src/Memory/page_fault_minor -D _GNU_SOURCE 

Run Command : ./src/Memory/page_fault_minor

page-fault_major.c (Major):
--------------
Build Command: gcc-9  -g src/Memory/page-fault_major.c -o src/Memory/page-fault_major

Run Command : ./src/Memory/page-fault_major <file with size greater than a few mbs>


ping_in_icmp.c : 
-----------------
Build Command : gcc-9  -g src/Network/ping_in_icmp.c -o src/Network/ping_in_icmp
Run Command : sudo ./src/Network/ping_in_icmp <host ip>


Socket based remote measurements:
--------------------------
ping_in_tcp_server_remote.c:
Build Command: gcc-9  -g src/Network/ping_in_tcp_server_remote.c -o src/Network/ping_in_tcp_server_remote


ping_in_tcp_client.c:
Build Command : gcc-9  -g src/Network/ping_in_tcp_client.c -o src/Network/ping_in_tcp_client

Running Files : 
Run Command : ./src/Network/ping_in_tcp_server_remote  (on server)
Run Command : sudo ./src/Network/ping_in_tcp_client (in terminal with hostname set that of remote on line 155)

Socket based local measurements:
--------------------------
ping_in_tcp_server.c:
Build Command: gcc-9  -g src/Network/ping_in_tcp_server.c -o src/Network/ping_in_tcp_server


ping_in_tcp_client.c:
Build Command : gcc-9  -g src/Network/ping_in_tcp_client.c -o src/Network/ping_in_tcp_client

Running Files : 
Run Command : ./src/Network/ping_in_tcp_server  (in one terminal)
Run Command : sudo ./src/Network/ping_in_tcp_client (in another terminal with hostname set to "127.0.0.1" in line 155 ### servaddr.sin_addr.s_addr = inet_addr("192.168.43.90");  ###)


TCP based local measurements (WORKING):
-------------------------------
tcp_client_startup_and_tear_down.c: 
Build Command : gcc-9  -g src/Network/tcp_client_startup_and_tear_down.c -o src/Network/tcp_client_startup_and_tear_down

Running files :
Run Command : ./src/Network/tcp_client_startup_and_tear_down (in another terminal with hostname set to "127.0.0.1" in line50 ###servaddr.sin_addr.s_addr = inet_addr("142.250.80.100");###)

TCP based remote measurements (WORKING):
-------------------------------
tcp_client_startup_and_tear_down.c: 
Build Command : gcc-9  -g src/Network/tcp_client_startup_and_tear_down.c -o src/Network/tcp_client_startup_and_tear_down

Running files :
Run Command : ./src/Network/tcp_client_startup_and_tear_down (in another terminal with hostname set to "142.250.80.100" in line50 ###servaddr.sin_addr.s_addr = inet_addr("142.250.80.100");###)

