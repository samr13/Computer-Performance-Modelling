simple ClientOpen
{
    parameters:
        volatile double InterarrivalTime @unit(s) = default(250ms);
	string OutputFile = default("outputOpen.txt");
    gates:
	inout proxy;
}

simple Proxy
{
    parameters:
        volatile double ServiceTime @unit(s) = default(10ms);
	double hitRate = default(0.7);

        @display("i=block/routing");
    gates:
	inout client;
	inout router;
}

simple Router
{
    parameters:
        volatile double ServiceTime @unit(s) = default(5ms);

        @display("i=block/routing");
    gates:
	inout proxy;
	inout origin[];
}

simple Origin
{
    parameters:
        volatile double ServiceTime @unit(s) = default(150ms);

        @display("i=block/routing");
    gates:
        inout router;
}

network WebOpen
{
    types:
        channel WAN extends ned.DelayChannel {
            delay = 36ms;
        }
        channel LAN extends ned.DelayChannel {
            delay = 0ms;
        }

    submodules:
        client : ClientOpen;
	proxy : Proxy;
	router : Router;
	originA : Origin {
		ServiceTime=150ms;
	}
	originB : Origin {
		ServiceTime=100ms;
	}

    connections:
	client.proxy <--> LAN <--> proxy.client;
	proxy.router <--> WAN <--> router.proxy;
	router.origin++ <--> LAN <--> originA.router;
	router.origin++ <--> LAN <--> originB.router;
}
