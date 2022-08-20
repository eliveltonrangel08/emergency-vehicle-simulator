

class EmergencyVehicle:

    def __init__(self, ev_type="Ambulance", priority=0):
        self.ev_type = ev_type
        self.priority = priority

class EmergencyEvent:

    def __init__(self, event_type, event_risk_level):
        self.event_type = event_type
        self.event_risk_level = event_risk_level


def main():

    ev = EmergencyVehicle(ev_type="Fire Truck", priority=2)

    event = EmergencyEvent(event_type="fire", event_risk_level=8)


    kb = {
        emergency_type: {
            name: "fire",
            level: [x for x in range(8)]
        }
    }
