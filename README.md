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

Codes run on remote WSL in VS Code
1. File - contention_final.c
2. File - file_cache_size_final.c
3. File - file_read_final.c
4. Network - ping_in_icmp.c 
5. Network - ping_in_tcp_client.c 
6. Network - ping_in_tcp_server.c 
7. Network - tcp_client_startup_and_tear_down.c
8. Memory - cache_size_final.c
9. Memory - memory_bw.c 
10. Memory - page_fault.c (Minor Fault)
11. Memory - page-fault.c (Major fault)


VS code for windows : Compiler used VS Code
VS code files added in the github repository

Run commands :
Function_Overheads.c : 
-----------------------
C:\msys64\mingw64\bin\gcc.exe -fdiagnostics-color=always -g C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\Function_Overheads.c -o C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\Function_Overheads.exe

getpid.c:
----------
C:\msys64\mingw64\bin\gcc.exe -fdiagnostics-color=always -g C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\getpid.c -o C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\getpid.exe


loop_overhead.c:
--------------------
C:\msys64\mingw64\bin\gcc.exe -fdiagnostics-color=always -g C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\loop_overhead.c -o C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\loop_overhead.exe

new_process_cmd.c:
-------------------
C:\msys64\mingw64\bin\gcc.exe -fdiagnostics-color=always -g C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\new_process_cmd.c -o C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\new_process_cmd.ex

rdtsc.c:
---------
C:\msys64\mingw64\bin\gcc.exe -fdiagnostics-color=always -g C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\rdtsc.c -o C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\rdtsc.exe

thread.c 
----------
C:\msys64\mingw64\bin\gcc.exe -fdiagnostics-color=always -g C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\thread.c -o C:\Users\shahm\Downloads\Courses\UCSD\CSE221\Project\Codes\System_Profiler_CSE221\src\CPU\thread.exe



WSL on VS Code:
Compiler Used : gcc
 
contention_final.c:
---------------------
Build Command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/contention_final.c -o /home/monils/contention_final	
Run Command : (can vary num processes from 1 to 30.. Sudo needed to flush cache
sudo ./contention_final <num_processes>

file_cache_size_final.c:
-------------------------
Build Command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/file_cache_size_final.c -o /home/monils/file_cache_size_final
Run Command : (We downloaded the 10GB binary file from : https://testfiledownload.com/)
sudo ./file_cache_size_final 10GB.bin

file_read_final.c :
------------------- 
Prerequisities : 
1. Local Mode:
	1.1 Created files with names and sizes as the name of the file : "log1mb","log2mb","log4mb","log8mb","log16mb","log32mb","log64mb","log128mb"
2. Remote mode :
	2.1 Mounted remote file path using : sudo sshfs -o allow_other,IdentityFile=/home/monils/.ssh/id_rsa.pub  <username>@ieng6-ece-20.ucsd.edu:<remote_dir_path> /mnt/remote_dir
	2.2 Created files with names and sizes as the name of the file : "log8kb","log16kb","log32kb","log64kb","log128kb","log256kb","log512kb","log1mb"
	
Build command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/file_read_final.c -o /home/monils/file_read_final
Run Commands : 
sudo ./file_read_final 0 (Local)
sudo ./file_read_final 1 (Remote)


cache_size_final.c:
------------------- 
Build Command : 	/usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/cache_size_final.c -o /home/monils/cache_size_final -D _GNU_SOURCE
Run Command : ./cache_size_final

ping_in_icmp.c : 
-----------------
Build Command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/ping_in_icmp.c -o /home/monils/CSE221_dbasu/CSE221_Project/ping_in_icmp
Run Command : sudo ./ping_in_icmp <host ip>


Socket based remote measurements:
--------------------------
ping_in_tcp_server.c:
Build Command: /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_server.c -o /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_server


ping_in_tcp_client.c:
Build Command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_client.c -o /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_client
Run Command : sudo ./ping_in_tcp_client

Running Files : 
Run Command : ./ping_in_tcp_server  (on server)
Run Command : sudo ./ping_in_tcp_client (in terminal with hostname set that of remote on line 155)

Socket based local measurements:
--------------------------
ping_in_tcp_server.c:
Build Command: /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_server.c -o /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_server


ping_in_tcp_client.c:
Build Command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_client.c -o /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_client
Run Command : sudo ./ping_in_tcp_client

Running Files : 
Run Command : ./ping_in_tcp_server  (in one terminal)
Run Command : sudo ./ping_in_tcp_client (in another terminal with hostname set to "127.0.0.1" in line 155 ### servaddr.sin_addr.s_addr = inet_addr("192.168.43.90");  ###)


TCP based local measurements:
-------------------------------
ping_in_tcp_server.c:
Build Command: /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_server.c -o /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_server

tcp_client_startup_and_tear_down.c: 
Build Command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/tcp_client_startup_and_tear_down.c -o /home/monils/CSE221_dbasu/CSE221_Project/tcp_client_startup_and_tear_down

Running files :
Run Command : ./ping_in_tcp_server  (in one terminal)
Run Command : ./tcp_client_startup_and_tear_down (in another terminal with hostname set to "127.0.0.1" in line50 ###servaddr.sin_addr.s_addr = inet_addr("142.250.80.100");###)

TCP based remote measurements:
-------------------------------
ping_in_tcp_server.c:
Build Command: /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_server.c -o /home/monils/CSE221_dbasu/CSE221_Project/ping_in_tcp_server

tcp_client_startup_and_tear_down.c: 
Build Command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/tcp_client_startup_and_tear_down.c -o /home/monils/CSE221_dbasu/CSE221_Project/tcp_client_startup_and_tear_down

Running files :
Run Command : ./ping_in_tcp_server  (in one terminal)
Run Command : ./tcp_client_startup_and_tear_down (in another terminal with hostname set in line50 ###servaddr.sin_addr.s_addr = inet_addr("142.250.80.100");###)

TCP based remote measurements (WORKING):
-------------------------------
tcp_client_startup_and_tear_down.c: 
Build Command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/tcp_client_startup_and_tear_down.c -o /home/monils/CSE221_dbasu/CSE221_Project/tcp_client_startup_and_tear_down

Running files :
Run Command : ./tcp_client_startup_and_tear_down (in another terminal with hostname set to "142.250.80.100" in line50 ###servaddr.sin_addr.s_addr = inet_addr("142.250.80.100");###)

memory_bw.c:
------------
Build Command : /usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/memory_bw.c -o /home/monils/CSE221_dbasu/CSE221_Project/memory_bw -D _GNU_SOURCE

Run Command : ./memory_bw

page_fault.c (Minor):
--------------
/usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/page_fault.c -o /home/monils/CSE221_dbasu/CSE221_Project/page_fault -D _GNU_SOURCE 

Run Command : ./page_fault

page-fault.c (Major):
--------------
/usr/bin/gcc-9 -fdiagnostics-color=always -g /home/monils/CSE221_dbasu/CSE221_Project/page-fault.c -o /home/monils/CSE221_dbasu/CSE221_Project/page-fault

Run Command : ./page-fault <file with size greater than a few mbs>

