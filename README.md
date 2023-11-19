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
