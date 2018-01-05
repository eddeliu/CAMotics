/******************************************************************************\

    CAMotics is an Open-Source simulation and CAM software.
    Copyright (C) 2011-2017 Joseph Coffland <joseph@cauldrondevelopment.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

\******************************************************************************/

#pragma once

#include <gcode/Axes.h>

#include <cbang/StdTypes.h>
#include <cbang/json/JSON.h>

#include <limits>


namespace GCode {
  class PlannerConfig;

  class PlannerCommand : public cb::JSON::Serializable {
    uint64_t id;
    double velocity;

  public:
    PlannerCommand(uint64_t id) :
      id(id), velocity(std::numeric_limits<double>::max()) {}
    virtual ~PlannerCommand() {}

    virtual const char *getType() const = 0;

    uint64_t getID() const {return id;}

    virtual double getEntryVelocity() const {return velocity;}
    virtual void setEntryVelocity(double entryVel) {velocity = entryVel;}
    virtual double getExitVelocity() const {return velocity;}
    virtual void setExitVelocity(double exitVel) {velocity = exitVel;}
    virtual double getDeltaVelocity() const {return 0;}
    virtual double getLength() const {return 0;}
    virtual void restart(const Axes &position, const PlannerConfig &config) {}

    // From cb::JSON::Serializable
    void read(const cb::JSON::Value &value);
    void write(cb::JSON::Sink &sink) const;

    virtual void insert(cb::JSON::Sink &sink) const = 0;
  };
}
