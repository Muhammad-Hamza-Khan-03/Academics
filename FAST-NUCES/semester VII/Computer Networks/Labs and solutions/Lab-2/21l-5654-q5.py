import time

def get_cpu_usage():
    with open('/proc/stat', 'r') as f:
        
        line = f.readline()
        
        parts = line.split()
       
        
        user = int(parts[1])
        nice = int(parts[2])
        system = int(parts[3])
        idle = int(parts[4])
        iowait = int(parts[5])
       
    
        total_time = user + nice + system + idle + iowait
        idle_time = idle + iowait
       
        return total_time, idle_time

def cpu_util():
	int i=0;
    while i<5:
       
        total_time_1, idle_time_1 = get_cpu_usage()
        time.sleep(1)  
        
        total_time_2, idle_time_2 = get_cpu_usage()

        
        total_differ = total_time_2 - total_time_1
        idle_differ = idle_time_2 - idle_time_1

       
        if total_diff > 0:
            cpu_utilization = 100 * (1 - (idle_differ / total_differ))
        else:
            cpu_utilization = 0.0

        print(f"CPU Util time: {cpu_utilization:.2f}%")
        time.sleep(1)  

if __name__ == "__main__":
    cpu_util()
