import random
import json
class LogicBoxData:

    def randomize(self, type):
        self.box_rewards = { 'Rewards': [] }
        
        rare = [6,10,13,24] #barley,el primo,poco,rosa
        superrare = [4,18,19,25,34] #rico,darryl,penny,carl,jacky
        epic = [15,16,20,26,29] #piper,pam,frank,bibi,bea
        mythic = [11,17,21,32] #mortis,tara,gene,max,mr.p
        legendary = [5,12,23,28] #spike,crow,leon,sandy
        
        
        boxes = open('boxes.json', 'r')
        Settings = boxes.read()
        
        BoxData = json.loads(Settings)
        
        
        #print(json.dumps([
        #    { 'id': 10, 'money': [15, 35], 'pp':[3, 20], 'pplength': [1, 2], 'multiplier': 20, 'gems':[3, 12], 'doublers':[200], 'boxtype': 0}, #brawlbox
        #    { 'id': 12, 'money': [29, 100], 'pp':[35, 89], 'pplength': [2, 2], 'multiplier': 2, 'gems':[4, 18], 'doublers':[200,400], 'boxtype': 1}, #bigbox
        #    { 'id': 11, 'money': [101, 299], 'pp':[80, 130], 'pplength': [5, 5], 'multiplier': 5, 'gems':[6, 24], 'doublers':[200,400,600], 'boxtype': 1}, #megabox
        #    { 'id': 14, 'money': [300, 499], 'pp':[150, 350], 'pplength': [8, 11], 'multiplier': 8, 'gems':[12, 24], 'doublers':[400,600,800], 'boxtype': 1} #ultrabox
        #]))
    
        #print(BoxData)
    
        for i in range(1): #boxes in box 
        
            
            for i in range(len(BoxData)):
                if type == BoxData[i]['id']:
                    if int(BoxData[i]['boxtype']) == 1:
                        gold_value = random.randint(BoxData[i]['money'][0], BoxData[i]['money'][1])
                        gold_reward = {'Amount': gold_value, 'DataRef': [0, 0], 'Value': 7}
                        self.box_rewards['Rewards'].append(gold_reward)
                        self.player.resources[1]['Amount'] = self.player.resources[1]['Amount'] + gold_value
                        self.player.db.update_player_account(self.player.token, 'Resources', self.player.resources)
                        
                        if len(self.player.brawlers_unlocked) < BoxData[i]['pplength'][1]:
                            rewarded = []
                            for x in range(len(self.player.brawlers_unlocked)):
                                pp_value = random.randint(BoxData[i]['pp'][0], BoxData[i]['pp'][1])
                                brawler = random.choice(sorted(set(self.player.brawlers_unlocked) - set(rewarded)))
                                if (self.player.brawlers_level[str(brawler)] < 8):
                                    pp_reward = {'Amount': pp_value, 'DataRef': [16, brawler], 'Value': 6}
                                    self.box_rewards['Rewards'].append(pp_reward)
                                    self.player.brawlers_powerpoints[str(brawler)] = self.player.brawlers_powerpoints[ str(brawler)] + pp_value
                                    self.player.db.update_player_account(self.player.token, 'BrawlersPowerPoints', self.player.brawlers_powerpoints)
                                    rewarded.append(brawler)
                        else:
                            rewarded = []
                            for x in range(random.randint(BoxData[i]['pplength'][0],BoxData[i]['pplength'][1])):
                                    pp_value = random.randint(BoxData[i]['pp'][0], BoxData[i]['pp'][1])
                                    brawler = random.choice(sorted(set(self.player.brawlers_unlocked) - set(rewarded)))
                                    if (self.player.brawlers_level[str(brawler)] < 8):
                                        pp_reward = {'Amount': pp_value, 'DataRef': [16, brawler], 'Value': 6}
                                        self.box_rewards['Rewards'].append(pp_reward)
                                        self.player.brawlers_powerpoints[str(brawler)] = self.player.brawlers_powerpoints[ str(brawler)] + pp_value
                                        self.player.db.update_player_account(self.player.token, 'BrawlersPowerPoints', self.player.brawlers_powerpoints)
                                        rewarded.append(brawler)
                    
                    
                        chance = random.randrange(0, 100)
                        multiplier = BoxData[i]['multiplier']
                        canDrop = []
                        if(chance < self.player.LegendaryChance * multiplier): canDrop = legendary
                        elif(chance < self.player.MythicChance * multiplier): canDrop = mythic
                        elif(chance < self.player.EpicChance * multiplier): canDrop = epic
                        elif(chance < self.player.SuperRareChance * multiplier): canDrop = superrare
                        elif(chance < self.player.RareChance * multiplier): canDrop = rare
        
                        
                        if(canDrop):
                            locked = [r for r in canDrop if r not in self.player.brawlers_unlocked]
                            
                            if(locked):
                                brawler = random.choice(locked)
                                
                                brawler_reward = {'Amount': 1, 'DataRef': [16, brawler], 'Value': 1}
                                self.box_rewards['Rewards'].append(brawler_reward)
                            
                                self.player.brawlers_unlocked.append(brawler)
                                self.player.db.update_player_account(self.player.token, 'UnlockedBrawlers',self.player.brawlers_unlocked)
                        
                        if (random.randint(0,100) < 50):
                            bonus = random.choice([2, 8])
                            b = random.choice([1,2])
                            if b == 1:
                                if (bonus == 8):
                                    bonus_value = random.randint(BoxData[i]['gems'][0], BoxData[i]['gems'][1])
                                    self.player.gems = self.player.gems + bonus_value
                                    self.player.db.update_player_account(self.player.token, 'Gems', self.player.gems)
                                else:
                                    bonus_value = random.choice(BoxData[i]['doublers'])
                                    self.player.token_doubler = self.player.token_doubler + bonus_value
                                    self.player.db.update_player_account(self.player.token, 'TokenDoubler', self.player.token_doubler)
                                bonus_reward = {'Amount': bonus_value, 'DataRef': [0, 0], 'Value': bonus}
                                self.box_rewards['Rewards'].append(bonus_reward)
                            else:
                                bonus_value = random.choice(BoxData[i]['doublers'])
                                self.player.token_doubler = self.player.token_doubler + bonus_value
                                self.player.db.update_player_account(self.player.token, 'TokenDoubler', self.player.token_doubler)
                                bonus_reward = {'Amount': bonus_value, 'DataRef': [0, 0], 'Value': 2}
                                self.box_rewards['Rewards'].append(bonus_reward)
                                bonus_value = random.randint(BoxData[i]['gems'][0], BoxData[i]['gems'][1])
                                self.player.gems = self.player.gems + bonus_value
                                self.player.db.update_player_account(self.player.token, 'Gems', self.player.gems)
                                bonus_reward = {'Amount': bonus_value, 'DataRef': [0, 0], 'Value': 8}
                                self.box_rewards['Rewards'].append(bonus_reward)
                    else:
                        chance = random.randrange(0, 100)
                        multiplier = BoxData[i]['multiplier']
                        canDrop = []
                        
                        if(chance < self.player.LegendaryChance * multiplier): canDrop = legendary
                        elif(chance < self.player.MythicChance * multiplier): canDrop = mythic
                        elif(chance < self.player.EpicChance * multiplier): canDrop = epic
                        elif(chance < self.player.SuperRareChance * multiplier): canDrop = superrare
                        elif(chance < self.player.RareChance * multiplier): canDrop = rare  
                        if canDrop: locked = [r for r in canDrop if r not in self.player.brawlers_unlocked] 
                        else: locked = []
                        if not locked or not canDrop:
                            gold_value = random.randint(BoxData[i]['money'][0], BoxData[i]['money'][1])
                            gold_reward = {'Amount': gold_value, 'DataRef': [0, 0], 'Value': 7}
                            self.box_rewards['Rewards'].append(gold_reward)
                            self.player.resources[1]['Amount'] = self.player.resources[1]['Amount'] + gold_value
                            self.player.db.update_player_account(self.player.token, 'Resources', self.player.resources)
                            
                            if len(self.player.brawlers_unlocked) < BoxData[i]['pplength'][1]:
                                rewarded = []
                                for x in range(len(self.player.brawlers_unlocked)):
                                    pp_value = random.randint(BoxData[i]['pp'][0], BoxData[i]['pp'][1])
                                    brawler = random.choice(sorted(set(self.player.brawlers_unlocked) - set(rewarded)))
                                    if (self.player.brawlers_level[str(brawler)] < 8):
                                        pp_reward = {'Amount': pp_value, 'DataRef': [16, brawler], 'Value': 6}
                                        self.box_rewards['Rewards'].append(pp_reward)
                                        self.player.brawlers_powerpoints[str(brawler)] = self.player.brawlers_powerpoints[ str(brawler)] + pp_value
                                        self.player.db.update_player_account(self.player.token, 'BrawlersPowerPoints', self.player.brawlers_powerpoints)
                                        rewarded.append(brawler)
                            else:
                                rewarded = []
                                for x in range(random.randint(BoxData[i]['pplength'][0],BoxData[i]['pplength'][1])):
                                        pp_value = random.randint(BoxData[i]['pp'][0], BoxData[i]['pp'][1])
                                        brawler = random.choice(sorted(set(self.player.brawlers_unlocked) - set(rewarded)))
                                        if (self.player.brawlers_level[str(brawler)] < 8):
                                            pp_reward = {'Amount': pp_value, 'DataRef': [16, brawler], 'Value': 6}
                                            self.box_rewards['Rewards'].append(pp_reward)
                                            self.player.brawlers_powerpoints[str(brawler)] = self.player.brawlers_powerpoints[ str(brawler)] + pp_value
                                            self.player.db.update_player_account(self.player.token, 'BrawlersPowerPoints', self.player.brawlers_powerpoints)
                                            rewarded.append(brawler)
                        
                        if(canDrop):
                            
                            
                            if(locked):
                                brawler = random.choice(locked)
                                
                                brawler_reward = {'Amount': 1, 'DataRef': [16, brawler], 'Value': 1}
                                self.box_rewards['Rewards'].append(brawler_reward)
                            
                                self.player.brawlers_unlocked.append(brawler)
                                self.player.db.update_player_account(self.player.token, 'UnlockedBrawlers',self.player.brawlers_unlocked)
                        
                        if (random.randint(0,100) < 50):
                            bonus = random.choice([2, 8])
                            b = random.choice([1,2])
                            if b == 1:
                                if (bonus == 8):
                                    bonus_value = random.randint(BoxData[i]['gems'][0], BoxData[i]['gems'][1])
                                    self.player.gems = self.player.gems + bonus_value
                                    self.player.db.update_player_account(self.player.token, 'Gems', self.player.gems)
                                else:
                                    bonus_value = random.choice(BoxData[i]['doublers'])
                                    self.player.token_doubler = self.player.token_doubler + bonus_value
                                    self.player.db.update_player_account(self.player.token, 'TokenDoubler', self.player.token_doubler)
                                bonus_reward = {'Amount': bonus_value, 'DataRef': [0, 0], 'Value': bonus}
                                self.box_rewards['Rewards'].append(bonus_reward)
                            else:
                                bonus_value = random.choice(BoxData[i]['doublers'])
                                self.player.token_doubler = self.player.token_doubler + bonus_value
                                self.player.db.update_player_account(self.player.token, 'TokenDoubler', self.player.token_doubler)
                                bonus_reward = {'Amount': bonus_value, 'DataRef': [0, 0], 'Value': 2}
                                self.box_rewards['Rewards'].append(bonus_reward)
                                bonus_value = random.randint(BoxData[i]['gems'][0], BoxData[i]['gems'][1])
                                self.player.gems = self.player.gems + bonus_value
                                self.player.db.update_player_account(self.player.token, 'Gems', self.player.gems)
                                bonus_reward = {'Amount': bonus_value, 'DataRef': [0, 0], 'Value': 8}
                                self.box_rewards['Rewards'].append(bonus_reward)
        
        
        return self.box_rewards  
