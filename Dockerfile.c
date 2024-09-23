FROM rockylinux:9.2

LABEL maintainer="Karl Schroeder <karl@subrock.com>"

# Pre-reqs
RUN yum install -y ca-certificates net-tools java-1.8.0-openjdk iputils nodejs npm which procps chkconfig openssl-devel gcc glibc glibc-common wget unzip httpd php gd gd-devel perl autoconf gettext automake && yum clean all -y

# Install Jmeter
RUN wget -O apache-jmeter-5.6.3.tgz https://dlcdn.apache.org//jmeter/binaries/apache-jmeter-5.6.3.tgz && tar xzf apache-jmeter-5.6.3.tgz -C /usr/local/
RUN cp -r /usr/local/apache-jmeter-5.6.3/* /usr/local/

# Install Jmeter Plugins
COPY post.tgz /tmp/
RUN tar xfz /tmp/post.tgz -C /usr/local/
WORKDIR /usr/local/lib/
RUN java  -jar cmdrunner-2.2.jar --tool org.jmeterplugins.repository.PluginManagerCMD install-all-except jpgc-hadoop,jpgc-oauth,ulp-jmeter-autocorrelator-plugin,ulp-jmeter-videostreaming-plugin,ulp-jmeter-gwt-plugin,tilln-iso8583
COPY jmeter.properties /usr/local/bin/
COPY rocky-jmeter-run /usr/local/bin/
COPY install_test_script.jmx /usr/local/bin/

WORKDIR /usr/local/bin/

# Expose port so its available in desktop.
EXPOSE 80

CMD ["/bin/bash"]

