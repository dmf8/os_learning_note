class Futex:
    locked, waits = '', ''

    def tryacquire(self):
        if not self.locked:
            # Test-and-set (cmpxchg)
            # Same effect, but more efficient than xchg
            self.locked = '🔒'
            return ''
        else:
            return '🔒'

    def release(self):
        if self.waits: # has other wait thread
            self.waits = self.waits[1:]
        else:
            self.locked = '' # no other wait, unlock

    @thread
    def t1(self):
        while True:
            if self.tryacquire() == '🔒':     # User
                self.waits = self.waits + '1'  # Kernel
                while '1' in self.waits:      # Kernel
                    pass # in real case, kernal will determine when to awake this thread
            cs = True                         # User
            del cs                            # User
            self.release()                    # Kernel
            # 每次释放都会进内核，更优的做法是通过计数器，在存在拥堵时（等待队列非空）才进内核

    @thread
    def t2(self):
        while True:
            if self.tryacquire() == '🔒':
                self.waits = self.waits + '2'
                while '2' in self.waits:
                    pass
            cs = True
            del cs
            self.release()

    @thread
    def t3(self):
        while True:
            if self.tryacquire() == '🔒':
                self.waits = self.waits + '3'
                while '3' in self.waits:
                    pass
            cs = True
            del cs
            self.release()

    @marker
    def mark_t1(self, state):
        if localvar(state, 't1', 'cs'):
            return 'blue'

    @marker
    def mark_t2(self, state):
        if localvar(state, 't2', 'cs'):
            return 'green'

    @marker
    def mark_t3(self, state):
        if localvar(state, 't3', 'cs'):
            return 'yellow'

    @marker
    def mark_both(self, state):
        count = 0
        for t in ['t1', 't2', 't3']:
            if localvar(state, t, 'cs'):
                count += 1
        if count > 1:
            return 'red'
