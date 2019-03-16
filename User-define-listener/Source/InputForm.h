/*
 * Copyright (c) 2019 Asit Dhal.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class InputForm  : public Component,
    public Label::Listener
{
public:
    InputForm();
    ~InputForm();

    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void clearActivated(InputForm*, bool isActive) = 0;
        virtual void submitActivated(InputForm*, bool isActive) = 0;
    };

    void addListener(Listener* listenerToAdd);
    void removeListener(Listener* listenerToRemove);

    void paint (Graphics&) override;
    void resized() override;
    
    void labelTextChanged(Label *labelThatHasChanged) override;
    
    void submit();
    void clear();

private:
    void clearActivate(bool isActive);
    void submitActivate(bool isActive);

    Label m_usernameLabel;
    Label m_passwordLabel;
    Label m_usernameInput;
    Label m_passwordInput;

    bool m_clearActive;
    bool m_submitActive;
    ListenerList<Listener> m_listeners;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputForm)
};
