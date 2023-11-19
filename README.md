# rocky-jmeter
Jmeter on top of Rocky Linux 9.

## Run
```
docker run --name rocky-jmeter -d -t -p 8001:80 subrock/rocky-jmeter
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
