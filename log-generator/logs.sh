#!/bin/bash

logfile=/tmp/myapp/file.log

status_list=(200 202 204 300 301 302 400 401 403 404 500)
method_list=("GET" "POST" "HEAD")
user_list=("John" "Tom" "Bill" "Dana" "Avi" "Yossi")

while $true; do
    status=${status_list[$(( RANDOM % ${#status_list[@]} ))]}
    method=${method_list[$(( RANDOM % ${#method_list[@]} ))]}
    user=${user_list[$(( RANDOM % ${#user_list[@]} ))]}
    ip=$(printf "%d.%d.%d.%d\n" "$((RANDOM % 256))" "$((RANDOM % 256))" "$((RANDOM % 256))" "$((RANDOM % 256))")
    price=$(( RANDOM % 10000 ))
    
    json=$(jq -n -c --arg status "$status" --arg method "$method" --arg user "$user" --arg ip "$ip" --arg price "$price" \
        '{status: ($status | tonumber), user: $user, method: $method, ip: $ip, price: ($price | tonumber)}')

    echo "$json"

    
    sleep 3
done

