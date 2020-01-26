install:
	# Install required packages
	pkg ins -y wget openjdk8 tomcat-native postgresql12
	
	# Create Jira user
	pw useradd jira -s /bin/sh -d /usr/local/jira

	# Enable and init PostgreSQL DB
	sysrc postgresql_enable="YES"
	service postgresql initdb

	# Add PostgreSQL conf files
	cp templates/postgresql.conf /var/db/postgres/data12/
	cp templates/pg_hba.conf /var/db/postgres/data12/

	# Create log file
	touch /var/db/postgres/data12/postgresql.log

	# Start Postgresql DB
	service postgresql start
