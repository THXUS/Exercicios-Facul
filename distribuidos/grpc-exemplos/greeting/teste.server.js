var PROTO_PATH = __dirname + '/teste.proto';
var grpc = require("@grpc/grpc-js");
var protoLoader = require("@grpc/proto-loader");

var packageDefinition = protoLoader.loadSync(
  PROTO_PATH, {
    keepCase: true,
    longs: String,
    enums: String,
    defaults: true, 
    oneofs: true
  });


function cbGreet() {
  return  {
    message: 'Hi, there!',
  };
}

function getGreet(call, callback) {
  callback(null, cbGreet(call.request));
}

var routeguide = grpc.loadPackageDefinition(packageDefinition);

function getServer() {
  var server = new grpc.Server();

  server.addService(routeguide.RouteGuide.service, {
    getGreet: getGreet
  });

  return server;
}
var routeServer = getServer();

routeServer.bindAsync('0.0.0.0:50051', grpc.ServerCredentials.createInsecure(), () => {
  routeServer.start();
});
