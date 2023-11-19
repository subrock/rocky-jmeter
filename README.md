# rocky-jmeter
Jmeter on top of Rocky Linux 9.

## Run
To add more WORKER nodes modify your jmeter.properties remote_hosts. 
```
docker network create --driver bridge rocky-jmeter-network
docker run --name CONTROLLER --hostname CONTROLLER --network rocky-jmeter-network -d -t subrock/rocky-jmeter:controller
docker run --name WORKER-1 --hostname WORKER-1 --network rocky-jmeter-network -d -t subrock/rocky-jmeter:worker
```

## Compose
You can build and launch using compose. Create a directory and place Dockerfile, docker-compose.yaml and startup.sh in a directory.
```
docker compose build
docker compose up
docker compose up -d
```
## Access
```
docker exec -it CONTROLLER bash
```
## Run Tests (JMX Scripts)
The WORKER nodes automatically start /usr/local/bin/jmeter-server. For your convenience there is a script /usr/local/bin/**rocky-jmeter-run** you can use to launch your JMX scripts with default runtime properties. The script should work without additional configuration. 

To add additional WORKER nodes modify docker-compose.yaml and specify additional containers. Make sure to update **remote_hosts** in /usr/local/bin/jmeter.properties on the CONTROLLER node. 
```
docker cp <your JMX> CONTROLLER:/usr/local/bin/
docker exec -it CONTROLLER /usr/local/bin/rocky-jmeter-run <your JMX>
```
For example you can use a simple JMX script already present on the CONTROLLER to verify things are working. 
```
docker exec -it CONTROLLER /usr/local/bin/rocky-jmeter-run install_test_script.jmx
```
## Scaling WORKER nodes
### RUN
```
docker network create --driver bridge rocky-jmeter-network
docker run --name CONTROLLER --hostname CONTROLLER --network rocky-jmeter-network -d -t subrock/rocky-jmeter:controller
docker run --name WORKER-1 --hostname WORKER-1 --network rocky-jmeter-network -d -t subrock/rocky-jmeter:worker
docker run --name WORKER-2 --hostname WORKER-2 --network rocky-jmeter-network -d -t subrock/rocky-jmeter:worker
```
Modify /usr/local/bin/jmeter.properties remote_hosts value. ex;
```
remote_hosts=WORKER-1, WORKER-2
```
### Compose
You can scale both the base image and latest images via compose. Here we create a docker-compose.yaml without a Docker file. 
```
version: "3"
services:
  controller:
    tty: true
    container_name: CONTROLLER
    hostname: CONTROLLER
    image: subrock/rocky-jmeter:controller
    restart: unless-stopped
    command: "/bin/bash"

  worker-1:
    tty: true
    container_name: WORKER-1
    hostname: WORKER-1
    image: subrock/rocky-jmeter:worker
    restart: unless-stopped
    command: "/bin/bash"

  worker-2:
    tty: true
    container_name: WORKER-2
    hostname: WORKER-2
    image: subrock/rocky-jmeter:worker
    restart: unless-stopped
    command: "/bin/bash"
```
Then we build it. 
```
docker compose build
docker compose up
docker compose up -d
```
Now you should see multiple WORKER nodes running. Next step is to modify jmeter.properties as above.
## Special Note
If you wanted to connect remotely from a client install of Jmeter you will need to expose port **1099** on the WORKER nodes. For example WORKER-1 = 1099:1099, WORKER-2 = 1100, 1099, etc. Ensure /usr/local/bin/rmi_keystore.jks matches your client.
