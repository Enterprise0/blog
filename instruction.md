## proxy
----
```bash
export http_proxy=http://proxyAddress:port
export http_proxy=http://127.0.0.1:10809
export all_proxy=socks5://127.0.0.1:10808
```

## update-alternatives
----
```bash
sudo update-alternatives --list python
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2.7 1
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.8 2
sudo update-alternatives --config python
```

## terminal
----
```bash
ctrl + alt+t 	 	# start terminal
ctrl + shift + +	# zoom in
ctrl + -		# zoom out
ctrt + shift + t 	# create new terminal
ctrl + shift + w 	# delete current terminal
ctrl + pageup/pagedown  # switch terminal
```

## screen
----
```bash
screen
screen -ls		# list all session
screen -S <name>	# create new session
screen -d <name>	# detach session
screen -r <name>	# recovery session

ctrl + a then d		# detach current session
ctrl + a then w		# list all windows
ctrl + a then k		# kill
 
ctrl + a then c 	# create new window
ctrl + a then n/p/num	# switch to next/previous/specific window 

ctrl + a then S 	# split window up and down
ctrl + a then X		# delete current block
ctrl + a then tab	# switch block

```

## USB pen
```bash
sudo mount -o remount,rw /dev/sda
```
