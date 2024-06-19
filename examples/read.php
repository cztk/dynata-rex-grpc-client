#!/usr/bin/php
<?php

date_default_timezone_set("Europe/Berlin");

function connect_socket(&$sock) {
	try {
	$sock = stream_socket_client('unix:///usr/local/run/dynata-rex-grpc-client/dynata-rex-grpc-client.sock', $errno, $errstr, 3);
	}catch(Exception $e) {}
}

class MysqliConnector {
    private ?\Mysqli $mysqli = null;

    private string $host = '::1';
    private int $port = 3306;
    private ?string $socket = null;
    private int $flags = MYSQLI_CLIENT_COMPRESS;
    private string $auth_user = 'demo';
    private string $auth_password = 'demo';
    private string $default_database = 'drex_grpc';
    private string $default_charset = 'utf8mb4';
    private string $timezone = 'Europe/Berlin';

    public function __construct() {
    }

    public function getConnection(): ?\Mysqli
    {
	    if(!$this->checkConnection()) {
		    echo "MysqliConnector need to connect to\n";
            #Logger::getInstance()->append('debug', 'MysqliConnector need to connect to '. $this->host);
		    if(!$this->reconnect()) {
			    echo "MysqliConnector could not connect\n";
                #Logger::getInstance()->append('debug', 'MysqliConnector could not connect to '. $this->host);
                return null;
            } else {
                #Logger::getInstance()->append('debug', 'MysqliConnector connected to '. $this->host);
            }
        }
        return $this->mysqli;
    }

    private function checkConnection(): bool
    { try {
	    if(null == $this->mysqli) {
		    $this->reconnect();
            #return false;
        }
        $_ping = $this->mysqli->ping();
        if(!$_ping) {
            #Logger::getInstance()->append('debug', 'MysqliConnector '. $this->host.' ping failed, gone away');
	}
    }catch(Exception|Throwable){ return false; }
        return $_ping;
    }

    private function reconnect(): bool
    {
        $this->mysqli = mysqli_init();
        if(false !== $this->mysqli) {
            if(!$this->mysqli->options(MYSQLI_SET_CHARSET_NAME, $this->default_charset)) {
                #Logger::getInstance()->append('warn', 'MysqliConnector could not set default_charset to '. $this->default_charset .' for host '. $this->host);
            }
	    try {

		    if ($this->mysqli->real_connect($this->host, $this->auth_user, $this->auth_password, $this->default_database, $this->port, $this->socket, $this->flags)) {
			    $this->mysqli->query("SET time_zone = '".$this->timezone."';");
                    return true;
		    } else {
			    echo "MysqliConnector could not connect to host \n";
                    #Logger::getInstance()->append('error', 'MysqliConnector could not connect to host ' . $this->host . ' ' . $this->mysqli->errno .': '. $this->mysqli->error);
                }
	    }catch(\mysqli_sql_exception $e) {
		    echo "MysqliConnector could not connect to host \n". $e->getMessage() . "\n";
                #Logger::getInstance()->append('error', 'MysqliConnector could not connect to host '. $this->host . ' ' . $this->mysqli->errno .': '. $this->mysqli->error . ' ' . $e->getMessage());
            }
	} else {
		echo "MysqliConnector could not init mysqli object\n";
            #Logger::getInstance()->append('error', 'MysqliConnector could not init mysqli object ');
        }
        return false;
    }
}



#in_data cls
#{"session": "3e839c9c-b0e6-4cc5-a2df-642290ab1d50", "start": 1, "end": 0, "group_id": 251590471, "timestamp": "2024-03-24T20:48:25.822Z"}

#in_data cls
#{"session": "e6f1c41a-3622-43fd-8ff9-29bc05b1bbba", "start": 0, "end": 1, "disposition": 1, "status": 0, "timestamp": "2024-03-24T20:48:26.659Z"}


$mysql = new MysqliConnector();


function insert_items($insert_items) {
	$mysql = $GLOBALS['mysql']->getConnection();

	/* create a prepared statement */
	$stmt = $mysql->stmt_init();
	$stmt->prepare("INSERT INTO disposition_status SET session = ?, timestamp = ?, start = ?, end = ?, group_id = ?, disposition = ?, status = ?, timestamp_event = ? ");
	/* bind parameters for markers */
	$stmt->bind_param('ssiiiiis', $session, $timestamp_c, $start, $end, $group_id, $disposition, $status, $timestamp);

	foreach($insert_items as $insert_item) {
	$session = $insert_item['session'] ?? '';
	$start = $insert_item['start'] ?? 0;
	$end = $insert_item['end'] ?? 0;
	$group_id = $insert_item['group_id'] ?? 0;
	$disposition = $insert_item['disposition'] ?? 0;
	$status = $insert_item['status'] ?? 0;
	$timestamp = $insert_item['timestamp'] ?? 0;
	$timestamp_c = date("Y-m-d H:i:s", strtotime($timestamp));
	/* execute query */
	$stmt->execute();
	}
	$stmt->close();
}



$in_data = '';
$sock = NULL;
connect_socket($sock);

$loop = 0;
while(true) {
	try {
		$in_data .= fread($sock, 4096);
	} catch(Exception|Throwable $e) { $in_data = false; }
	if(false == $in_data) { sleep(1); connect_socket($sock); continue; }

	if(10 == $loop) {
	if("\n" == substr($in_data, -1)) {
		$data = explode("\n", trim($in_data));
		$insert_items = [];
		foreach($data as $in) {
			$insert_items[] = json_decode($in, true);
			#echo json_last_error_msg()."\n";
		}
		try {
			insert_items($insert_items);
		} catch(Exception|Throwable $e) {var_dump($e);}
		$in_data = '';
	}
	}
	$loop++;
}

fclose($sock);
