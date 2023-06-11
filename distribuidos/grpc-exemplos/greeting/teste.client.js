var PROTO_PATH = __dirname + '/teste.proto';
var grpc = require('@grpc/grpc-js');
var protoLoader = require('@grpc/proto-loader');

var packageDefinition = protoLoader.loadSync(
  PROTO_PATH, {
    keepCase: true,
    longs: String,
    enums: String,
    defaults: true,
    oneofs: true
  });

var routeguide = grpc.loadPackageDefinition(packageDefinition);


var client = new routeguide.RouteGuide('localhost:50051',
                                       grpc.credentials.createInsecure());

client.getGreet( {}, (err, feature)=> {

  if(err) {
    console.log("erro", err);
    return;
  }
  console.log(`Greeting: ${feature.message}`);
} );