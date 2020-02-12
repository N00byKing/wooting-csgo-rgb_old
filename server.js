http = require('http');
fs = require('fs');
port = 3000;
host = '127.0.0.1';
  
wooting_interface = require('./build/Release/wooting_interface');

server = http.createServer( function(req, res) {

    if (req.method == 'POST') {
        res.writeHead(200, {'Content-Type': 'text/html'});

        var body = '';
        req.on('data', function (data) {
            body += data;
        });
        req.on('end', function () {
            wooting_interface.wooting_handle_event(body);
        	res.end( '' );
        });
    }
});

server.listen(port, host);
console.log('Listening at http://' + host + ':' + port);