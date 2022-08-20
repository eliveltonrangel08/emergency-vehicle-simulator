import random
import string

import traci
import os
import sys
import sumolib
import time

import enum


# sys.setrecursionlimit(10**7)

class GeoCoordinates:
    """
    """

    def __init__(self, X=None, Y=None):
        self.X = X
        self.Y = Y

    def getCoordinates(self):
        return {"X": self.X, "Y": self.Y}

    def setCoordinates(self, X, Y):
        self.X = X
        self.Y = Y

    def getCoordinatesOSM(self):
        return self.Y, self.X


class Route:
    def __init__(self, from_coord, to_coord, sumo_net):
        self.fromCoord = from_coord
        self.toCoord = to_coord
        self.sumo_net = sumo_net

    def getClosestEdge(self, coordinates):
        x, y = self.sumo_net.convertLonLat2XY(coordinates.Y, coordinates.X)
        edges = net.getNeighboringEdges(x, y, 5)
        closest_edge = None
        if len(edges) > 0:
            distances_and_edges = sorted([(dist, edge) for edge, dist in edges])
            dist, closest_edge = distances_and_edges[0]
        return closest_edge

    def getShortestPath(self):

        fromEdge = self.getClosestEdge(self.fromCoord)
        toEdge = self.getClosestEdge(self.toCoord)

        if fromEdge and toEdge:
            return self.sumo_net.getShortestPath(fromEdge, toEdge)
        return None


class Vehicle:
    def __init__(self, guiShape='passenger', id='default', type='default', accel=0.8, decel=4.5, sigma=0.5, length=5,
                 minGap=3, maxSpeed=16.67):
        self.guiShape = guiShape
        self.id = id
        self.type = type
        self.accel = accel
        self.decel = decel
        self.sigma = sigma
        self.length = length
        self.minGap = minGap
        self.maxSpeed = maxSpeed

    def __repr__(self):
        return f"Vehicle(guiShape={self.guiShape}, id={self.id})"

    def getSumoTag(self):
        return f'   <vType id="{self.id}" guiShape="{self.guiShape}" type="{self.type}" accel="{self.accel}" decel="{self.decel}" sigma="{self.sigma}" length="{self.length}" minGap="{self.minGap}" maxSpeed="{self.maxSpeed}" />\n'


class EventVehicleType(enum.Enum):
    EMERGENCY = Vehicle(guiShape='emergency', type='emergency', id="v_emergency", maxSpeed=30)
    FIRE = Vehicle(guiShape='firebrigade', type='emergency', id="v_firebrigade", maxSpeed=28, length=7)
    POLICE = Vehicle(guiShape='police', type='emergency', id="v_police", maxSpeed=28)


class EmergencyEvent:
    def __init__(self, vehicle_type=None, sumo_net=None):
        self.vehicle_type = vehicle_type
        self.sumo_net = sumo_net

    def __repr__(self):
        print(self.__str__())

    def get_random_event_route(self):
        route = None
        self.sumo_net = net
        if not self.sumo_net:
            raise BaseException("Net object not defined")
        while not route:
            ev_from = random.choice(self.sumo_net.getEdges())
            ev_to = random.choice(self.sumo_net.getEdges())
            route = self.sumo_net.getShortestPath(ev_from, ev_to)
        return route


# End classes

def get_default_coordinates():
    return [GeoCoordinates(-22.90184,-47.05810),  # Início da PD
            GeoCoordinates(-22.90358,-47.06265),  # Final da PD
            GeoCoordinates(-22.90428,-47.06233),  # Maria quitéria NS Início
            GeoCoordinates(-22.90305,-47.05763),  # Maria quitéria NS Fim
            GeoCoordinates(-22.90189,-47.06120),  # Maria quitéria SN Início
            GeoCoordinates(-22.90489,-47.05971),  # Maria quitéria SN Fim
            GeoCoordinates(-22.90548,-47.05914),
            GeoCoordinates(-22.90106,-47.05992)]
    # return [
    #     # GeoCoordinates(-12.2375,-38.9459),  # Início da JD NS
    #     # GeoCoordinates(-12.2662,-38.9537),  # Final da JD NS
    #     # GeoCoordinates(-12.2735,-38.9555),  # Início da JD SN
    #     # GeoCoordinates(-12.2370,-38.9455),  # Final da JD SN
    #     GeoCoordinates(-12.2637,-38.9465),  # Início da PD OL
    #     GeoCoordinates(-12.2596,-38.9658),  # Final da PD OL
    #     GeoCoordinates(-12.2597,-38.9674),  # Início da PD LO
    #     GeoCoordinates(-12.2622,-38.9491),  # Final da PD LO
    #     GeoCoordinates(-12.251493, -38.954660),  # Maria quitéria NS Início
    #     GeoCoordinates(-12.266223, -38.955197),  # Maria quitéria NS Fim
    #     GeoCoordinates(-12.266935, -38.954921),  # Maria quitéria SN Início
    #     GeoCoordinates(-12.251601, -38.954418),  # Maria quitéria SN Fim
    #
    #     # GeoCoordinates(-12.2505, -38.9596),
    #     # GeoCoordinates(-12.2583, -38.9493),
    #     # GeoCoordinates(-12.2581, -38.9454),
    #     # GeoCoordinates(-12.2552, -38.9635),
    # ]


def get_vehicles():
    return [Vehicle(guiShape='emergency', id='v_emergency', type='emergency', maxSpeed=30),
            Vehicle(guiShape='firebrigade', id='v_firebrigade', type='emergency', maxSpeed=28, length=7),
            Vehicle(guiShape='police', id='v_police', type='emergency', maxSpeed=28), ]


def id_generator(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))


def get_random_event_route(sumo_net):
    route = [None]
    while not route[0]:
        ev_from = random.choice(sumo_net.getEdges())
        ev_to = random.choice(sumo_net.getEdges())
        route = sumo_net.getShortestPath(ev_from, ev_to)
    return route


def generate_router_file():
    coordinates = get_default_coordinates()
    with open(f'{path}/{prefix}.rou.xml', 'w') as outf:
        sumolib.xml.writeHeader(outf, root="routes")
        v_id = 0
        outf.write(Vehicle(guiShape='passenger', id='v_passenger', type='passenger').getSumoTag())
        outf.write(Vehicle(guiShape='bus', id='v_bus', type='bus', length=10).getSumoTag())
        for v in get_vehicles():
            outf.write(v.getSumoTag())

        routes = []
        main_route = Route(coordinates[0], coordinates[1], net).getShortestPath()
        outf.write(f'   <route cost="{main_route[1]}" id="0" edges="{" ".join([e.getID() for e in main_route[0]])}" />\n')

        routes.append(main_route)

        for id in range(2, n_routes, 2):
            route = Route(coordinates[id], coordinates[id+1], net).getShortestPath()
            outf.write(f'   <route cost="{route[1]}" id="{int(id/2)}" edges="{" ".join([e.getID() for e in route[0]])}" />\n')
            # route = Route(random.choice(coordinates), random.choice(coordinates), net).getShortestPath()
            # while not route[0]:
            #     route = Route(random.choice(coordinates), random.choice(coordinates), net).getShortestPath()
            # outf.write(
            #     f'   <route cost="{route[1]}" id="{id}" edges="{" ".join([e.getID() for e in route[0]])}" />\n')
            routes.append(route)

        flowId = 0
        for i in range(n_flows):
            route_index = random.randint(0, len(routes) - 1)
            '<flow id="flow0" type="vtype0" route="route0" begin="0" period="3" number="10"/>'

            outf.write(f'   <flow id="flow{flowId}" type="v_passenger" route="{route_index}" begin="0" period="3" number="{n_vehicles_flow}"/>\n')

            p_bus = 1. / int((n_flows/10)*100)
            p_emergency = 1. / int((n_flows/25)*100)

            if random.uniform(0, 1) < p_emergency:
                vehicle = random.choice(get_vehicles())
                outf.write(
                    f'   <flow id="evFlow{flowId}" type="{vehicle.id}" route="{route_index}" begin="0" period="{i}" number="{int(n_vehicles_flow/25)}"/>\n')
                # outf.write(f'   <vehicle id="{vId}" depart="{float(i)}" route="0" type=""/>\n')
                flowId += 1
            if random.uniform(0, 1) < p_bus:
                outf.write(
                    f'   <flow id="busFlow{flowId}" type="v_bus" route="{route_index}" begin="0" period="{i}" number="{int(n_vehicles_flow/10)}"/>\n')
                # outf.write(
                #     f'   <vehicle id="{vId}" depart="{float(i)}" route="{route_index}" type="v_bus" color="0,1,0"/>\n')
            flowId += 1
        vId = 0
        for i in range(n_vehicles):
            route_index = random.randint(0, len(routes) - 1)
            outf.write(f'   <vehicle id="veh{vId}" depart="{float(i)}" route="{route_index}" type="v_passenger"/>\n')
            vId += 1

        outf.write('</routes>\n')


def run():
    """execute the TraCI control loop"""
    step = 0
    # we start with phase 2 where EW has green
    tl_id = "1040148526"
    traci.trafficlight.setPhase(tl_id, 2)

    while traci.simulation.getMinExpectedNumber() > 0:
        traci.simulationStep()
        new_vehicles = []
        # if traci.trafficlight.getPhase(tl_id) == 2:
        #     # we are not already switching
        #     if traci.inductionloop.getLastStepVehicleNumber("detector0") > 0:
        #         print("Acendeu")
        #         # there is a vehicle from the north, switch
        #         # traci.trafficlight.setPhase(tl_id, 3)
        #     else:
        #         pass
                # otherwise try to keep green for EW
                # traci.trafficlight.setPhase(tl_id, 2)
        if random.uniform(0, 1) < PROB_NEW_VEHICLE:
            vehicle = Vehicle(guiShape='passenger', id='v_passenger', maxSpeed=30)
            edges = get_random_event_route(net)
            edges = [e.getID() for e in edges[0]]
            traci.route.add(routeID=id_generator(), edges=edges)

            traci.vehicle.add(vehID=id_generator(4), typeID=vehicle.id, routeID=1)


        if random.uniform(0, 1) < PROB_EVENT:
            vehicle = random.choice(list(EventVehicleType)).value

            vId = id_generator()
            rId = id_generator(10)
            new_vehicles.append(vId)

            # Add random event
            edges = get_random_event_route(net)
            edges = [e.getID() for e in edges[0]]
            print(f"Novo evento: {vId, rId}")
            # Add new route
            traci.route.add(routeID=rId, edges=edges)

            traci.vehicle.add(vehID=vId, typeID=vehicle.id, routeID=1)

            print(f"Lista de Veículos ativos: {traci.vehicle.getIDList()}")
        # if any(item in new_vehicles for item in traci.vehicle.getIDList()):
        #     print("Veículo na Pista!")
        #     time.sleep(5)
        step += 1
    traci.close()
    sys.stdout.flush()
    print("Finalizou")


# this is the main entry point of this script
if __name__ == "__main__":
    sumo_home = os.environ['SUMO_HOME'] = os.path.join('/opt', 'sumo')
    sys.path.append(sumo_home)
    sys.path.append(os.path.join(sumo_home, 'bin'))
    sumoBinary = traci.sumolib.checkBinary('sumo-gui')
    path = os.getenv('PATH_APP')
    prefix = os.getenv('PREFIX_FILE')

    net = sumolib.net.readNet(f'{path}/{prefix}.net.xml')

    PROB_EVENT = 1. / 1000000
    PROB_NEW_VEHICLE = 1. / 100000
    random.seed(7)
    n_routes = 8
    n_vehicles = 10
    n_flows = 10
    n_vehicles_flow = 50

    # generate_router_file()

    # this is the normal way of using traci. sumo is started as a
    # subprocess and then the python script connects and runs
    traci.start([sumoBinary, "-c", f"{path}/{prefix}.sumo.cfg",
                 "--tripinfo-output", f"{path}/tripinfo.xml"])
    run()
