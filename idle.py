import sys

IDLE=0
ACTIVE=1
UNKNOWN=2

def cpu_count_at_status(cpu_status_dict, query_status):
  cpu_count = 0
  for c, status in cpu_status_dict.items():
    if status == query_status:
      cpu_count += 1  
  return cpu_count

def main(argv):
  num_cpus = 40
  cpu_status = {}
  idle_ns = 0
  all_idle_begin_ts = None
  begin_ts = None
  end_ts = None
  target_period_begin_ts = int(argv[2])
  target_period_end_ts = int(argv[3])
  for c in range(0, num_cpus):
    cpu_status[c] = UNKNOWN  
  with open(argv[1], 'r') as fo:
    for l in fo.readlines():
      tokens = l.split()
      if (len(tokens) < 3):
       continue
      ts = int(tokens[0])
      cpu = int(tokens[1])
      if begin_ts is None:
        begin_ts = ts
      end_ts = ts
      if tokens[2] == 'IDLE_OFF':
        cpu_status[cpu] = ACTIVE
      else:
        cpu_status[cpu] = IDLE
      if cpu_count_at_status(cpu_status, IDLE) == num_cpus:
        all_idle_begin_ts = ts 
        all_idle_end_ts = None
      else:
        all_idle_end_ts = ts 
      if all_idle_begin_ts is not None and all_idle_end_ts is not None:  
        if all_idle_begin_ts >= target_period_begin_ts and all_idle_end_ts <= target_period_end_ts:
          idle_ns += all_idle_end_ts - all_idle_begin_ts 
        all_idle_begin_ts = None
        all_idle_end_ts = None
  print(target_period_begin_ts, target_period_end_ts, target_period_end_ts - target_period_begin_ts)
  print(idle_ns)

if __name__ == "__main__":
  main(sys.argv)
